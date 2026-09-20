#include <stdint.h>

/* Four warps x sixteen lanes = 64 pixels in flight.
 *
 * Every warp starts at PC 0 and runs this same program, so they differentiate
 * on warp_id(). Warp w draws rows w, w+NWARPS, w+2*NWARPS ... which means the
 * finished image is identical to the single-warp render -- that is the point,
 * it makes the result verifiable rather than merely plausible.
 *
 * Set FRAMES to 0 for an endless zoom (needs a cycle limit), or to N to draw
 * N frames and terminate -- then `complete` fires and the sim stops itself.
 *
 * Set warp_count in the testbench to match NWARPS. */

#define NLANES     16
#define LANE_SHIFT  4      /* log2(NLANES) -- must match */
#define NWARPS      4
#define FRAMES      1      /* 0 = endless zoom; N = draw N frames then terminate */

static inline int laneid(void) {
    int r;
    __asm__ volatile(".insn r 0x0B, 0, 0, %0, x0, x0" : "=r"(r));
    return r;
}

static inline int warpid(void) {
    int r;
    __asm__ volatile(".insn r 0x0B, 0, 1, %0, x0, x0" : "=r"(r));
    return r;
}

static inline void terminate(void) {
    __asm__ volatile(".insn r 0x0B, 0, 2, x0, x0, x0");
}

static inline int ballot(int p) {
    int r;
    __asm__ volatile(".insn r 0x0B, 0, 4, %0, %1, x0" : "=r"(r) : "r"(p));
    return r;
}

static inline int tmc(int m) {
    int old;
    __asm__ volatile(".insn r 0x0B, 0, 5, %0, %1, x0" : "=r"(old) : "r"(m));
    return old;
}

/* Every (warp, lane) pair is an independent thread and needs its own stack,
 * or spilled per-thread values collide. 4 KB each; at 2x16 that is 128 KB
 * below 0x8000000, well clear of the program. */
__attribute__((naked, section(".text.unlikely"))) void _start(void) {
    __asm__ volatile(
        ".option push\n"
        ".option norelax\n"
        "la   gp, __global_pointer$\n"
        ".option pop\n"
        ".insn r 0x0B, 0, 1, t0, x0, x0\n"   /* t0 = warp  */
        "slli t0, t0, 4\n"                    /* warp * NLANES (LANE_SHIFT) */
        ".insn r 0x0B, 0, 0, t1, x0, x0\n"   /* t1 = lane  */
        "add  t0, t0, t1\n"                   /* thread index */
        "slli t0, t0, 12\n"                   /* * 4 KB */
        "li   sp, 0x8000000\n"
        "sub  sp, sp, t0\n"
        "call main\n"
        "loop: j loop\n"
    );
}

static void putc_(char c) { *((volatile unsigned int*)0x70000000) = c; }
static void puts_(const char* s) { while (*s) putc_(*s++); }
/* Arithmetic, not a table lookup: a load here would make a garbled digit
 * ambiguous between "the value is wrong" and "the load is wrong". */
static void hex_(unsigned int v) {
    for (int i = 7; i >= 0; i--) {
        unsigned int d = (v >> (i * 4)) & 0xF;
        putc_((char)(d < 10 ? ('0' + d) : ('A' + d - 10)));
    }
}

/* Print from one lane only, so a line appears once per warp instead of 16
 * times. The warp is chosen by the caller with a uniform branch. */
static void say(const char* label, unsigned int v) {
    int old = tmc(1);
    puts_(label); hex_(v); putc_('\n');
    tmc(old);
}

#define SCALE 1024
#define MAX_ITER 32

static unsigned int iter_to_color(int iter) {
    unsigned int t = (unsigned int)iter & (MAX_ITER - 1);
    unsigned int r = (t * 8) & 0xFF;
    unsigned int g = (t * 5) & 0xFF;
    unsigned int b = (t * 13) & 0xFF;
    return (r << 16) | (g << 8) | b;
}

int main(void) {
    volatile unsigned int* frame = (volatile unsigned int*)0x10000000;

    const int lane = laneid();
    const int warp = warpid();

    say("warp ", (unsigned int)warp);

    const int cx = -768, cy = 0;

    /* Clear only this warp's own rows. No cross-warp interference, so no
     * barrier is needed -- there is no barrier instruction anyway. */
    for (int py = warp; py < 240; py += NWARPS)
        for (int px = 0; px < 320; px += NLANES)
            frame[320 * py + px + lane] = 0;

    for (int f = 0; FRAMES == 0 || f < FRAMES; f++) {

        /* The zoom level comes from the shared timer, not a per-warp counter.
         * Warps run free with no barrier, so a local counter drifts: warp 0
         * ends up drawing step 0 while warp 2 draws step 8, and since step 8
         * sits inside the main cardioid its rows come out solid black. One
         * clock read keeps every warp on the same frame. */
        const int step = FRAMES ? 0 : (int)((*(volatile unsigned int*)0x08000004 >> 18) & 7);

        int zoom = 1536;
        for (int i = 0; i < step; i++) zoom = (zoom * 3) / 4;

        int x_step = (zoom * 2) / 320;
        int y_step = (zoom * 2 * 240 / 320) / 240;
        if (x_step < 1) x_step = 1;
        if (y_step < 1) y_step = 1;

        /* Corner derived from the step actually used, not from zoom. The
         * divisions above truncate, so the window really sampled is
         * 320*x_step wide rather than 2*zoom -- and taking the corner from
         * zoom puts that whole shortfall on the right, i.e. the centre drifts
         * left. The error grows as a fraction of the width as zoom shrinks,
         * which is why it looks like the image slides sideways as it zooms. */
        const int x_start = cx - x_step * 160;
        const int y_start = cy - y_step * 120;

        /* Warp w takes every NWARPS-th row. py is warp-uniform, so the loop
         * test is uniform and safe to branch on. */
        for (int py = warp; py < 240; py += NWARPS) {
            int ci = y_start + py * y_step;

            for (int px = 0; px < 320; px += NLANES) {
                int my_px = px + lane;
                int cr = x_start + my_px * x_step;
                int zr = 0, zi = 0, iter = 0;

                int outer = (1 << NLANES) - 1;

                for (int i = 0; i < MAX_ITER; i++) {
                    int zr2 = (zr * zr) >> 10;
                    int zi2 = (zi * zi) >> 10;
                    int zrzi = zr * zi;

                    /* Uniform across the warp, so branching on it is safe. */
                    int active = ballot((zr2 + zi2) <= 4 * SCALE);
                    if (active == 0) break;

                    int nzr = zr2 - zi2 + cr;
                    int nzi = ((2 * zrzi) >> 10) + ci;

                    tmc(active);
                    /* "+r" marks these live across the masked region so GCC
                     * does not reuse their registers as scratch beforehand. */
                    __asm__("mv %0, %1" : "+r"(zr) : "r"(nzr));
                    __asm__("mv %0, %1" : "+r"(zi) : "r"(nzi));
                    __asm__("addi %0, %0, 1" : "+r"(iter));
                }

                tmc(outer);

                frame[320 * py + my_px] = iter_to_color(iter);
            }
        }
    }

    say("done ", (unsigned int)warp);

    terminate();
    while (1) { __asm__ volatile("nop"); }   /* unreachable */
}
