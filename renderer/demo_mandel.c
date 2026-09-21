#include "gpu.h"
#include "raster.h"

/* Mandelbrot: one continuous zoom, then hand over.
 *
 * Unlike the other scenes this one is FRAME-COUNTED rather than run to a
 * wall-clock deadline -- the point is a single complete zoom, and how long
 * that takes is whatever the machine manages. It costs nothing to get right
 * either: a frame counter is warp-uniform by construction, so unlike the
 * timed scenes there is no need for one warp to decide and a barrier to
 * publish the decision.
 *
 * Fixed point is Q14, against the Q10 of programs/mandelbrot_warp.c, which
 * runs out of resolution after about 10x. Two things are needed to get there
 * and both were found by modelling the integer arithmetic on the host rather
 * than by looking at frames:
 *
 * ZOOM STEP IS CARRIED WITH 8 EXTRA FRACTION BITS. step = step*250/256 once
 * a frame truncates downward every time, and that bias COMPOUNDS -- a decay
 * that should land at 64 after 240 frames reaches 2 instead, at which point
 * (px*step)>>SUB maps 320 pixels onto ten distinct values and the screen is
 * vertical stripes. Carrying the step scaled by 256 makes the per-frame loss
 * 1/256 of a unit and the decay tracks the real exponential.
 *
 * THE ZOOM STOPS AT step == 1<<SUB. Below that, adjacent pixels share a
 * coordinate; this is the floor Q14 imposes, and it is what bounds the zoom
 * at ~205x. Zooming past it does not show more, it shows less.
 *
 * |z| IS CLAMPED. A lane that escapes keeps iterating -- it is masked off so
 * it never commits, but the arithmetic still runs -- and one step past |z|=2
 * reaches |z|=6, so zr*zi would peak near (6<<14)^2 = 9.7e9 and overflow
 * int32. Clamping each component to 2.5<<14 caps the product at 1.7e9. It
 * cannot change the picture: anything past 2.5 has already escaped, and 2.5
 * squared is 6.25, still outside the radius-2 test, so a clamped lane can
 * never re-enter. */

#ifndef NWARPS_M
#define NWARPS_M 4
#endif
_Static_assert(NWARPS_M == NWARPS_R, "scene warp counts must match");

#ifndef TARGET_FPS
#define TARGET_FPS 60
#endif
#define FRAME_US (1000000u / TARGET_FPS)

#ifndef ZOOM_FRAMES
#define ZOOM_FRAMES 240
#endif

#define SHIFT  14
#define SUB    6                      /* step carried at 1/64 unit */
#define STEPQ  8                      /* extra fraction bits on the zoom */
#define LIM    (40960)                /* 2.5 in Q14 */
/* Boundary point with structure at every scale -- the middle of the set is a
 * black screen and the outside is a flat wash. */
#define CX     (-12184)               /* -0.743644 in Q14 */
#define CY     ( 2160)                /*  0.131826 in Q14 */
#ifndef STEP0
#define STEP0  13107                  /* half-width 2.0 */
#endif
#define STEPMIN (1 << SUB)            /* one coordinate unit per pixel */
#define ZNUM   250                    /* per-frame zoom factor, 250/256 */
#define ZDEN   256
#ifndef IT0
#define IT0    48
#endif
#define ITMAX  128

#define BB raster_fb

/* Triangle wave on 0..255, branchless. A per-lane branch would be resolved
 * from one lane's register and give fifteen pixels the wrong colour. */
static inline unsigned int tri(unsigned int x) {
    unsigned int t = x & 255;
    return ((t ^ (unsigned int)(-(int)(t >> 7))) & 127) << 1;
}

static inline unsigned int mcol(int iter, int maxit) {
    unsigned int t = (unsigned int)iter * 7;
    unsigned int c = (tri(t) << 16) | (tri(t + 85) << 8) | tri(t + 170);
    /* Inside the set goes near-black. Also branchless. */
    { unsigned int ins = (unsigned int)(-(iter >= maxit)); return (c & ~ins) | (0xFF00FFu & ins); }
}

void mandel_scene(int nframes) {
    const int lane = laneid();
    const int warp = warpid() & (NWARPS_M - 1);
    const int full = ~0;

    int stepq = STEP0 << STEPQ;
    unsigned int next = TIMER_US + FRAME_US;

    for (int f = 0; f < nframes; f++) {
        /* Iteration budget grows with depth: shallow frames do not need it
         * and deep ones fall apart without it. Warp-uniform, so the loop
         * bound below is safe to branch on. */
        int step  = stepq >> STEPQ;
        int maxit = IT0 + f / 2;
        if (maxit > ITMAX) maxit = ITMAX;

        int x0 = CX - ((SCREEN_W / 2) * step >> SUB);
        int y0 = CY - ((SCREEN_H / 2) * step >> SUB);

        /* Warp w owns rows w, w+NWARPS_M, ... so no warp touches another's
         * pixels and the present needs no barrier before it. */
        for (int py = warp; py < SCREEN_H; py += NWARPS_M) {
            int ci = y0 + (py * step >> SUB);
            int base = py * SCREEN_W;

            for (int px = 0; px < SCREEN_W; px += NLANES) {
                int mx = px + lane;
                int cr = x0 + (mx * step >> SUB);
                int zr = 0, zi = 0, iter = 0;

                for (int i = 0; i < maxit; i++) {
                    int zr2 = (zr * zr) >> SHIFT;
                    int zi2 = (zi * zi) >> SHIFT;
                    /* Uniform across the warp, so branching on it is safe --
                     * and it retires whole warps early, which is where the
                     * outside of the set gets its speed. */
                    int active = ballot((zr2 + zi2) <= (4 << SHIFT));
                    if (active == 0) break;

                    int nzr = zr2 - zi2 + cr;
                    /* zr*zi >> (SHIFT-1) is 2*zr*zi >> SHIFT without ever
                     * forming 2*zr*zi, which is what would overflow. */
                    int nzi = ((zr * zi) >> (SHIFT - 1)) + ci;
                    /* Ternaries, not ifs: -march=rv32im_zbb turns these into
                     * min/max, which are branchless. An `if` here would be a
                     * per-lane branch resolved from one lane's register. */
                    nzr = nzr >  LIM ?  LIM : nzr;
                    nzr = nzr < -LIM ? -LIM : nzr;
                    nzi = nzi >  LIM ?  LIM : nzi;
                    nzi = nzi < -LIM ? -LIM : nzi;

                    tmc(active);
                    __asm__("mv %0, %1" : "+r"(zr) : "r"(nzr));
                    __asm__("mv %0, %1" : "+r"(zi) : "r"(nzi));
                    __asm__("addi %0, %0, 1" : "+r"(iter));
                }
                tmc(full);

                BB[base + mx] = mcol(iter, maxit);
            }
        }

        raster_present();

        if (warpid() == 0) {
            if ((int)(TIMER_US - next) > 0) next = TIMER_US;
            else while ((int)(TIMER_US - next) < 0) { }
            next += FRAME_US;
        }
        barrier(NWARPS_M);

        stepq = stepq * ZNUM / ZDEN;
        if (stepq < (STEPMIN << STEPQ)) stepq = STEPMIN << STEPQ;
    }
}

#ifndef DEMO_COMBINED
int main(void) {
    if (warpid() == 0) wspawn(NWARPS_M, (void*)0);
    for (;;) mandel_scene(ZOOM_FRAMES);
    return 0;
}
#endif
