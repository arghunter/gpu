#include "gpu.h"



#define NWARPS    4
#define FRAMES    0      
/* Fixed-point scale for the complex plane. Raising it from 1024 to 8192
 * buys three more bits of zoom depth: the window can shrink until x_step
 * hits its floor of 1, so the deepest view is SCREEN_W/SCALE units across --
 * 0.31 at 1024, 0.039 here.
 *
 * The ceiling is overflow in the iteration. |z| escapes at 2, so zr peaks at
 * 2*SCALE = 16384; zr*zr is 2.7e8 and the 2*zr*zi term 5.4e8, both clear of
 * int32. SCALE = 16384 would put 2*zr*zi at 2.1e9 and wrap. */
#define SCALE      8192
#define SCALE_BITS 13
/* ---- zoom target -----------------------------------------------------
 *
 * Select with -DZOOM_TARGET=n. Each target carries its own iteration count,
 * because how deep the escape-time bands go varies hugely by region: the
 * open areas resolve at 64, but the filaments in seahorse valley collapse
 * into flat colour below about 128.
 *
 * The centres are written as decimals and folded to integers at compile
 * time -- no floating point reaches the hardware, which has none. */
#define TARGET_NECK      0      /* -0.75,   0      the neck, dendrites   */
#define TARGET_SEAHORSE  1      /* -0.745,  0.113  seahorse valley       */
#define TARGET_ELEPHANT  2      /*  0.275,  0.007  elephant valley       */
#define TARGET_TRIPLE    3      /* -0.088,  0.654  triple spiral         */

#ifndef ZOOM_TARGET
#define ZOOM_TARGET TARGET_SEAHORSE
#endif

/* Start part-way into the zoom. Reaching the interesting depth takes ~25
 * frames, which is minutes of simulation -- -DSTART_STEP=n skips straight
 * there. The cycle wraps back to START_STEP so a preview stays in range. */
#ifndef START_STEP
#define START_STEP 0
#endif

#if   ZOOM_TARGET == TARGET_NECK
#  define CENTER_RE  (-0.75)
#  define CENTER_IM  ( 0.0)
#  define MAX_ITER   64
#elif ZOOM_TARGET == TARGET_SEAHORSE
#  define CENTER_RE  (-0.745)
#  define CENTER_IM  ( 0.113)
#  define MAX_ITER   128
#elif ZOOM_TARGET == TARGET_ELEPHANT
#  define CENTER_RE  ( 0.275)
#  define CENTER_IM  ( 0.007)
#  define MAX_ITER   128
#elif ZOOM_TARGET == TARGET_TRIPLE
#  define CENTER_RE  (-0.088)
#  define CENTER_IM  ( 0.654)
#  define MAX_ITER   128
#else
#  error "unknown ZOOM_TARGET"
#endif

/* Per-frame pacing. The render is fast enough on hardware that the zoom
 * blurs past; this holds each frame long enough to watch. Set to 0 to run
 * flat out, raise it to slow the zoom further. */
#define FRAME_NOPS 5000

static inline void frame_delay(void) {
    for (unsigned int i = 0; i < FRAME_NOPS; i++) __asm__ volatile("nop");
}

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

    /* Folded at compile time. Note the image runs +imaginary downward, but
     * the set is symmetric about the real axis so a target at +im and one at
     * -im look the same. */
    const int cx = (int)(CENTER_RE * SCALE);
    const int cy = (int)(CENTER_IM * SCALE);

    for (int py = warp; py < SCREEN_H; py += NWARPS)
        for (int px = 0; px < SCREEN_W; px += NLANES)
            frame[SCREEN_W * py + px + lane] = 0;

 
    int step = START_STEP;
    for (int f = 0; FRAMES == 0 || f < FRAMES; f++) {

        /* 7/8 per step rather than 3/4: a gentler ratio means many more
         * steps before x_step bottoms out, so the zoom runs far longer. */
        int zoom = 12288;
        for (int i = 0; i < step; i++) zoom = (zoom * 7) / 8;

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
                    int zr2 = (zr * zr) >> SCALE_BITS;
                    int zi2 = (zi * zi) >> SCALE_BITS;
                    int zrzi = zr * zi;


                    int active = ballot((zr2 + zi2) <= 4 * SCALE);
                    if (active == 0) break;

                    int nzr = zr2 - zi2 + cr;
                    int nzi = ((2 * zrzi) >> SCALE_BITS) + ci;

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

        frame_delay();

        /* 12288 * (7/8)^32 = 163, just above the point where x_step clamps
         * to 1 and the view stops shrinking. */
        step++;
        if (step > 32) step = START_STEP;
    }

    say("done ", (unsigned int)warp);
    warp_flush();
}
