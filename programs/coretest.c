#include <stdint.h>

/* Self-checking core testbench. Prints one line per test; anything that is not
 * "ok" is a hardware bug. Run at nLanes=1 first -- every test here is written
 * to be lane-uniform, so a failure at 1 lane is a scalar pipeline bug and a
 * failure that only appears at 8 lanes is a vectorisation bug.
 *
 * Reference values were computed on the host; see the checksum test. */

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

__attribute__((naked, section(".text.unlikely"))) void _start(void) {
    __asm__ volatile(
        ".option push\n"
        ".option norelax\n"
        "la   gp, __global_pointer$\n"
        ".option pop\n"
        "li   sp, 0x7000000\n"
        "la   a0, __bss_start\n"
        "la   a1, _end\n"
        "1:   bgeu a0, a1, 2f\n"
        "sw   zero, 0(a0)\n"
        "addi a0, a0, 4\n"
        "j    1b\n"
        "2:   call main\n"
        "loop: j loop\n"
    );
}

static void putc_(char c) { *((volatile unsigned int*)0x70000000) = c; }

static void puts_(const char* s) { while (*s) putc_(*s++); }

static void hex_(unsigned int v) {
    for (int i = 7; i >= 0; i--) putc_("0123456789ABCDEF"[(v >> (i * 4)) & 0xF]);
}

static int failures = 0;

static void check(const char* name, unsigned int got, unsigned int want) {
    puts_(name);
    if (got == want) {
        puts_(" ok\n");
    } else {
        failures++;
        puts_(" FAIL got=");
        hex_(got);
        puts_(" want=");
        hex_(want);
        putc_('\n');
    }
}

/* ---- 1. dependent ALU chain: back-to-back RAW on every instruction ---- */
static void t_alu(void) {
    int a = opaque(1);
    for (int i = 0; i < 64; i++) a = a * 3 + 1;      /* mul + add chain */
    check("alu_chain", (unsigned int)a, 0xB63E1B81u);

    int b = opaque(0x12345678);
    b = b ^ (b << 7); b = b ^ (b >> 9); b = b ^ (b << 13);
    check("alu_shift", (unsigned int)b, 0x64A2C5CDu);
}

/* ---- 2. load-use hazard at every distance 0..3 ---- */
static volatile int mem[8];

static void t_loaduse(void) {
    for (int i = 0; i < 8; i++) mem[i] = i * 7 + 1;

    int d0 = mem[3]; d0 += 1;                       /* use immediately */
    check("load_use_d0", (unsigned int)d0, 23u);

    int d1 = mem[4]; int pad1 = opaque(5); d1 += pad1;
    check("load_use_d1", (unsigned int)d1, 34u);

    int s = 0;
    for (int i = 0; i < 8; i++) s += mem[i];        /* 8 loads, accumulate */
    check("load_sum", (unsigned int)s, 204u);
}

/* ---- 3. store then load the same address ---- */
static void t_storeload(void) {
    volatile int* p = &mem[0];
    *p = 0xABCD;
    int v = *p;
    check("store_load_same", (unsigned int)v, 0xABCDu);

    for (int i = 0; i < 8; i++) mem[i] = 0;
    for (int i = 0; i < 8; i++) mem[i] = i + 100;
    int t = 0;
    for (int i = 0; i < 8; i++) t = t * 2 + mem[i];
    check("store_load_seq", (unsigned int)t, 25747u);
}

/* ---- 4. many outstanding loads: fill the request queue ---- */
static volatile int big[64];

static void t_queue(void) {
    for (int i = 0; i < 64; i++) big[i] = i * i;
    unsigned int h = 0;
    for (int i = 0; i < 64; i++) h = h * 31u + (unsigned int)big[i];
    check("load_queue64", h, 0x560843E0u);
}

/* ---- 5. multiply latency and dependent use ---- */
static void t_mul(void) {
    int x = opaque(12345);
    int y = opaque(6789);
    int lo = x * y;
    check("mul_lo", (unsigned int)lo, 83810205u);

    long long w = (long long)x * (long long)y;       /* mul + mulh */
    check("mulh_hi", (unsigned int)(unsigned long long)(w >> 32), 0u);

    int acc = opaque(1);
    for (int i = 1; i <= 12; i++) acc = acc * i;     /* 12! */
    check("mul_chain", (unsigned int)acc, 479001600u);
}

/* ---- 6. branch immediately after the compare that feeds it ---- */
static void t_branch(void) {
    int n = 0;
    for (int i = 0; i < 100; i++) { if (opaque(i) & 1) n += 2; else n += 1; }
    check("branch_alt", (unsigned int)n, 150u);

    int m = opaque(0);
    for (int i = 0; i < 32; i++) { int c = (opaque(i) * 7) % 5; if (c == 0) m++; }
    check("branch_mod", (unsigned int)m, 7u);
}

/* ---- 7. custom instructions ---- */
static void t_custom(void) {
    check("laneid", (unsigned int)laneid(), 0u);
    check("ballot_1", (unsigned int)ballot(1), (1u << NLANES) - 1u);
    check("ballot_0", (unsigned int)ballot(0), 0u);
    check("ballot_lane", (unsigned int)ballot(laneid() & 1), 0u);
}

/* ---- 8. the mandelbrot kernel itself, against host-computed values ---- */
#define SCALE 1024
#define MAX_ITER 32

static int escape(int cr, int ci) {
    int zr = 0, zi = 0, iter = 0;
    for (int i = 0; i < MAX_ITER; i++) {
        int a = zr * zr, b = zi * zi, c = zr * zi;
        int zr2 = a >> 10, zi2 = b >> 10;
        int cond = (zr2 + zi2) <= 4 * SCALE;
        if (cond == 0) break;
        int m = opaque(-cond);
        int nzr = zr2 - zi2 + cr;
        int nzi = ((2 * c) >> 10) + ci;
        zr = (nzr & m) | (zr & ~m);
        zi = (nzi & m) | (zi & ~m);
        iter += cond;
    }
    return iter;
}

static void t_mandel(void) {
    check("mandel_0_0",     (unsigned int)escape(-2304, -1152),  1u);
    check("mandel_160_120", (unsigned int)escape( -864,   -72), 32u);
    check("mandel_80_60",   (unsigned int)escape(-1584,  -612),  3u);
    check("mandel_240_180", (unsigned int)escape( -144,   468), 32u);
    check("mandel_8_120",   (unsigned int)escape(-2232,   -72),  1u);
    check("mandel_312_8",   (unsigned int)escape(  504, -1080),  2u);

    /* Every 8th pixel of the real frame: 1200 points, folded into one number.
     * This is the sensitive one -- a single wrong iter changes it. */
    unsigned int sum = 0;
    for (int py = 0; py < 240; py += 8)
        for (int px = 0; px < 320; px += 8)
            sum = sum * 31u + (unsigned int)escape(-2304 + px * 9, -1152 + py * 9);
    check("mandel_checksum", sum, 0x697E9B38u);
}

int main(void) {
    int probe; puts_("SP="); hex_((unsigned int)&probe); putc_('\n');
    puts_("=== coretest start ===\n");
    t_alu();
    t_loaduse();
    t_storeload();
    t_queue();
    t_mul();
    t_branch();
    t_custom();
    t_mandel();
    puts_("=== failures=");
    hex_((unsigned int)failures);
    puts_(" ===\n");
    *((volatile unsigned int*)0x70000008) = 100;
    while (1) { __asm__ volatile("nop"); }
}
