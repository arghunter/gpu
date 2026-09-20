#include <stdint.h>

/* Lane-identity testbench. Everything here is meaningless at nLanes=1, so run
 * it at the width you actually care about. Each line prints once per active
 * lane; for the ballot tests every lane should print the SAME value, and for
 * the per-lane tests the values should differ. */

#define NLANES 8
#define ALL ((1 << NLANES) - 1)

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
        "li   sp, 0x8000000\n"
        ".insn r 0x0B, 0, 0, t0, x0, x0\n"   /* t0 = laneid */
        "slli t0, t0, 12\n"                   /* 4 KB of stack per lane */
        "sub  sp, sp, t0\n"
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
static void show(const char* n, unsigned int v) { puts_(n); hex_(v); putc_('\n'); }

/* Uniform across lanes: prints the same value NLANES times. */
static void chk(const char* n, unsigned int got, unsigned int want) {
    puts_(n);
    if (got == want) { puts_(" ok\n"); }
    else { puts_(" FAIL got="); hex_(got); puts_(" want="); hex_(want); putc_('\n'); }
}

/* Kept out of line so `lane` has to survive a call, forcing a spill. */
__attribute__((noinline)) static int passthrough(int x) { return x + 0; }

static volatile int per_lane[NLANES];
static volatile int scratch;

int main(void) {
    int lane = laneid();

    /* ---- 1. raw lane id. Should print 0,1,2,...,NLANES-1 -- one per line. */
    show("lane=", (unsigned int)lane);

    /* ---- 2. ballot sees distinct lanes. Uniform: same value every line. */
    chk("ballot_odd",  (unsigned int)ballot(lane & 1),      0xAAu & ALL);
    chk("ballot_lo",   (unsigned int)ballot(lane < 4),      0x0Fu & ALL);
    chk("ballot_zero", (unsigned int)ballot(lane == 0),     0x01u);
    chk("ballot_top",  (unsigned int)ballot(lane == NLANES - 1), (1u << (NLANES - 1)));

    /* ---- 3. lane survives a function call, i.e. a spill and reload. */
    int spilled = passthrough(lane);
    chk("lane_spill", (unsigned int)ballot(spilled == lane), (unsigned int)ALL);

    /* ---- 4. each lane has its own stack. Addresses should be 4096 apart,
     * so bit 12 alternates between neighbours. */
    int local = lane;
    show("stackaddr=", (unsigned int)&local);
    chk("stack_private", (unsigned int)ballot(((unsigned int)&local >> 12) & 1), 0x55u & ALL);

    /* ---- 5. per-lane store address, then read it back. This is exactly what
     * the mandelbrot pixel store does. */
    per_lane[lane] = lane + 100;
    chk("store_perlane", (unsigned int)ballot(per_lane[lane] == lane + 100), (unsigned int)ALL);

    /* every lane should see every other lane's write too */
    chk("store_visible", (unsigned int)ballot(per_lane[NLANES - 1] == NLANES - 1 + 100),
        (unsigned int)ALL);

    /* ---- 6. all lanes writing the SAME address must not corrupt each other */
    scratch = lane;
    chk("store_shared", (unsigned int)ballot(scratch >= 0 && scratch < NLANES),
        (unsigned int)ALL);

    /* ---- 7. masking, if you still want it checked here */
    int old = tmc(0x55u & ALL);
    chk("mask_ballot", (unsigned int)ballot(1), 0x55u & ALL);
    tmc(old);
    chk("mask_restore", (unsigned int)ballot(1), (unsigned int)ALL);

    puts_("=== done ===\n");
    *((volatile unsigned int*)0x70000008) = 100;
    while (1) { __asm__ volatile("nop"); }
}
