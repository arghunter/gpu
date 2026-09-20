#include <stdint.h>


#define NLANES 1

static inline int opaque(int x) { __asm__ ("" : "+r"(x)); return x; }

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
    int x_start = cx - zoom;
    int y_start = cy - (zoom * 240 / 320);
    int x_step = (zoom * 2) / 320;
    int y_step = (zoom * 2 * 240 / 320) / 240;
    if (x_step < 1) x_step = 1;
    if (y_step < 1) y_step = 1;

    int lane = laneid();

    // trace("ballot=", (unsigned int)ballot(laneid() & 1));
    // trace("draw: cx=", (unsigned int)cx);
    // trace("draw: cy=", (unsigned int)cy);
    // trace("draw: zoom=", (unsigned int)zoom);
    // trace("draw: x_start=", (unsigned int)x_start);

    for (int py = 0; py < 240; py++) {
        int ci = y_start + py * y_step;
        for (int px = 0; px < 320; px += NLANES) {
            int my_px = px + lane;
// #if MANDEL_PROBE
//             if (py == 0 && px == 0) trace("my_px=", (unsigned int)my_px);
//             if (py == 0 && px == 0) trace("stack=", (unsigned int)&my_px);
// #endif
            int cr = x_start + my_px * x_step;
            int zr = 0;
            int zi = 0;
            int iter = 0;


            for (int i = 0; i < MAX_ITER; i++) {
                int zr2 = (zr * zr) >> 10;
                int zi2 = (zi * zi) >> 10;
                int zrzi = zr * zi;

                int cond = (zr2 + zi2) <= 4 * SCALE;

                /* Uniform across the warp, so branching on it is safe. This
                 * is what ballot buys us: the warp stops as soon as its last
                 * lane escapes instead of always running MAX_ITER times. */
                int alive = ballot(cond);
                if (alive == 0) break;

                /* Commit per-lane with arithmetic, not with tmc. Every lane
                 * executes every instruction, so nothing depends on a register
                 * surviving an instruction the lane skipped -- which is the
                 * one thing GCC will not preserve. opaque() stops it proving
                 * m is 0 or -1 and rewriting this back into a branch. */
                int m = opaque(-cond);

                int new_zr = zr2 - zi2 + cr;
                int new_zi = ((2 * zrzi) >> 10) + ci;

                zr = (new_zr & m) | (zr & ~m);
                zi = (new_zi & m) | (zi & ~m);
                iter += cond;
            }

// #if MANDEL_PROBE
//             /* py/px are warp-uniform, so this branch is safe. Prints once per
//              * lane, so you get all NLANES values for pixels 160..160+NLANES-1
//              * near the centre of the set. Expect 00000020 (= MAX_ITER). */
//             if (py == 120 && px == 160) {
//                 trace("mid iter=", (unsigned int)iter);
//             }
//             /* Store address per lane. Row 0 should be 10000000 + lane*4,
//              * row 1 should be 10000500 + lane*4 (0x500 = 320*4). */
//             if (py == 0 && px == 0) {
//                 trace("row0 addr=", (unsigned int)&frame[320 * py + my_px]);
//             }
//             if (py == 1 && px == 0) {
//                 trace("row1 addr=", (unsigned int)&frame[320 * py + my_px]);
//             }
// #endif

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
