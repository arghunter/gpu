#include "gpu.h"



#define NWARPS    4
#define FRAMES    0      
#define SCALE     1024
#define MAX_ITER  32

static unsigned int iter_to_color(int iter) {
    unsigned int t = (unsigned int)iter & (MAX_ITER - 1);
    return (((t * 8) & 0xFF) << 16) | (((t * 5) & 0xFF) << 8) | ((t * 13) & 0xFF);
}

int main(void) {
    volatile unsigned int* frame = FRAME_BUFFER;

    const int lane = laneid();
    const int warp = warpid();


    if (warp == 0) wspawn(NWARPS, (void*)0);

    say("warp ", (unsigned int)warp);

    const int cx = -768, cy = 0;

    for (int py = warp; py < SCREEN_H; py += NWARPS)
        for (int px = 0; px < SCREEN_W; px += NLANES)
            frame[SCREEN_W * py + px + lane] = 0;

 
    int step = 0;
    for (int f = 0; FRAMES == 0 || f < FRAMES; f++) {

        int zoom = 1536;
        for (int i = 0; i < step; i++) zoom = (zoom * 3) / 4;

        int x_step = (zoom * 2) / SCREEN_W;
        int y_step = (zoom * 2 * SCREEN_H / SCREEN_W) / SCREEN_H;
        if (x_step < 1) x_step = 1;
        if (y_step < 1) y_step = 1;


        const int x_start = cx - x_step * (SCREEN_W / 2);
        const int y_start = cy - y_step * (SCREEN_H / 2);

        for (int py = warp; py < SCREEN_H; py += NWARPS) {
            int ci = y_start + py * y_step;

            for (int px = 0; px < SCREEN_W; px += NLANES) {
                int my_px = px + lane;
                int cr = x_start + my_px * x_step;
                int zr = 0, zi = 0, iter = 0;

                for (int i = 0; i < MAX_ITER; i++) {
                    int zr2 = (zr * zr) >> 10;
                    int zi2 = (zi * zi) >> 10;
                    int zrzi = zr * zi;


                    int active = ballot((zr2 + zi2) <= 4 * SCALE);
                    if (active == 0) break;

                    int nzr = zr2 - zi2 + cr;
                    int nzi = ((2 * zrzi) >> 10) + ci;

                    MASKED(active) {
                        PMOV(zr, nzr);
                        PMOV(zi, nzi);
                        PINC(iter);
                    }
                }

                frame[SCREEN_W * py + my_px] = iter_to_color(iter);
            }
        }


        barrier(NWARPS);

        step++;
        if (step > 8) step = 0;
    }

    say("done ", (unsigned int)warp);
    warp_flush();
}
