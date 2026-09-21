#include <stdint.h>


#define NLANES 16

static inline int laneid(void) {
    int r;
    __asm__ volatile(".insn r 0x0B, 0, 0, %0, x0, x0" : "=r"(r));
    return r;
}

static inline int ballot(int p) {
    int r;
    __asm__ volatile(".insn r 0x0B, 0, 4, %0, %1, x0" : "=r"(r) : "r"(p));
    return r;
}

/* Predicated commit. dst is read-modify-write: masked-off lanes keep their old
 * value, and the "+r" constraint tells GCC dst is live across the masked
 * region so it cannot reuse the register as scratch beforehand. Writing
 * `dst = src` in plain C does not convey that and GCC will clobber dst. */
#define PMOV(dst, src) __asm__("mv %0, %1" : "+r"(dst) : "r"(src))
#define PINC(dst)      __asm__("addi %0, %0, 1" : "+r"(dst))

static inline int tmc(int m) {
    int old;
    __asm__ volatile(".insn r 0x0B, 0, 5, %0, %1, x0" : "=r"(old) : "r"(m));
    return old;
}


__attribute__((naked, section(".text.unlikely"))) void _start(void) {
    __asm__ volatile(
        ".option push\n"
        ".option norelax\n"
        "la   gp, __global_pointer$\n"
        ".option pop\n"
        "li sp, 0x8000000\n"
        ".insn r 0x0B, 0, 0, t0, x0, x0\n"
        "slli t0, t0, 12\n"
        "sub sp, sp, t0\n"
        "call main\n"
        "loop: j loop\n"
    );
}


void debug_log(char* character) {
    while (*character != '\0') {
        *((volatile unsigned int*)0x70000000) = *(character);
        *((volatile unsigned char*)0x8000034) = *(character);
        character++;
    }
}

void debug_num(unsigned int value) {
    *((volatile unsigned int*)0x70000008) = value;
}


static void debug_putc(char c) {
    char s[2] = { c, 0 };
    debug_log(s);
}

static void debug_hex32(unsigned int value) {
    static const char hex[] = "0123456789ABCDEF";
    for (int i = 7; i >= 0; i--) {
        debug_putc(hex[(value >> (i * 4)) & 0xF]);
    }
}

static void trace(char *label, unsigned int value) {
    debug_log(label);
    debug_hex32(value);
    debug_log("\n");
}

#define SCALE 1024
#define MAX_ITER 32

/* Set to 1 to print the escape count at the centre of the set. */
#define MANDEL_PROBE 1


/* MAX_ITER is a power of two, so iter == MAX_ITER folds to t == 0, which the
 * formula already maps to black. No branch and no mask needed. */
static unsigned int iter_to_color(int iter) {
    unsigned int t = (unsigned int)iter & (MAX_ITER - 1);
    unsigned int r = (t * 8) & 0xFF;
    unsigned int g = (t * 5) & 0xFF;
    unsigned int b = (t * 13) & 0xFF;

    return (r << 16) | (g << 8) | b;
}

void draw_mandelbrot(volatile unsigned int* frame, int cx, int cy, int zoom) {
    int x_step = (zoom * 2) / 320;
    int y_step = (zoom * 2 * 240 / 320) / 240;
    if (x_step < 1) x_step = 1;
    if (y_step < 1) y_step = 1;
    /* Corner from the truncated step, so the window stays centred on cx/cy
     * as zoom shrinks -- see mandelbrot_warp.c. */
    int x_start = cx - x_step * 160;
    int y_start = cy - y_step * 120;

    int lane = laneid();


    for (int py = 0; py < 240; py++) {
        int ci = y_start + py * y_step;
        for (int px = 0; px < 320; px += NLANES) {
            int my_px = px + lane;

            int cr = x_start + my_px * x_step;
            int zr = 0;
            int zi = 0;
            int iter = 0;


            int outer = (1 << NLANES) - 1;

            for (int i = 0; i < MAX_ITER; i++) {
                int zr2 = (zr * zr) >> 10;
                int zi2 = (zi * zi) >> 10;
                int zrzi = zr * zi;

                int active = ballot((zr2 + zi2) <= 4 * SCALE);
                if (active == 0) break;

                int nzr = zr2 - zi2 + cr;
                int nzi = ((2 * zrzi) >> 10) + ci;

                tmc(active);
                PMOV(zr, nzr);
                PMOV(zi, nzi);
                PINC(iter);
            }

            tmc(outer);

            frame[320 * py + my_px] = iter_to_color(iter);
        }
    }
}

int main() {
    volatile unsigned int* frame = (volatile unsigned int*)0x10000000;
    volatile unsigned int* timer = (volatile unsigned int*)0x8000004;

    debug_log("boot\n");

    int cx = -768;
    int cy = 0;
    int step = 0;

    while (1) {
        int ctime = *timer;

        // debug_log("frame: step=");
        // debug_hex32((unsigned int)step);
        // debug_log("\n");

        int zoom = 1536;
        for (int i = 0; i < step; i++) {
            zoom = (zoom * 3) / 4;
        }
        draw_mandelbrot(frame, cx, cy, zoom);

        step++;
        if (step > 8) step = 0;

        while (*timer - ctime < 5) {
            __asm__ volatile("nop");
        }
    }
}
