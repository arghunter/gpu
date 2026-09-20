#include <stdint.h>

/* Smallest possible store/load repro. Expect:
 *   A=0000ABCD  B=0000ABCD  C=00001234  D=00001234
 * Anything reading back 00000000 means the store never landed (or the load
 * never saw it). Keep this tiny so a printf in the RTL is readable. */

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
static void show(const char* n, unsigned int v) { puts_(n); hex_(v); putc_('\n'); }

static volatile unsigned int bss_word;

int main(void) {
    /* A: .bss, store then load, nothing in between */
    bss_word = 0xABCD;
    show("A=", bss_word);

    /* B: same location, read again after some unrelated work */
    volatile unsigned int spacer = 0;
    for (int i = 0; i < 10; i++) spacer += i;
    show("B=", bss_word);

    /* C: the stack, which is where GCC spills */
    volatile unsigned int stk = 0x1234;
    show("C=", stk);

    /* D: stack again through a pointer, so it cannot stay in a register */
    volatile unsigned int* p = &stk;
    *p = 0x1234;
    show("D=", *p);

    /* E: known-good control -- a .rodata load, which already works */
    show("E=", (unsigned int)"Z"[0]);

    *((volatile unsigned int*)0x70000008) = 100;
    while (1) { __asm__ volatile("nop"); }
}
