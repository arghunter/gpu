#include <stdint.h>

const unsigned char my_data[] = {
#embed "mesh.bin"
};

__attribute__((naked)) void _start(void) {
    __asm__ volatile(
        "li sp, 0x8000000\n"
        "call main\n"
        "loop: j loop\n"
    );
}

static inline int lane_id(void) {
    int r;
    __asm__ volatile(".insn r 0x0B, 0, 0, %0, x0, x0" : "=r"(r));
    return r;
}

static inline int warp_id(void) {
    int r;
    __asm__ volatile(".insn r 0x0B, 0, 1, %0, x0, x0" : "=r"(r));
    return r;
}

static inline void terminate(void) {
    __asm__ volatile(".insn r 0x0B, 0, 2, x0, x0, x0");
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

int main() {
    volatile unsigned int* frame = (volatile unsigned int*)0x10000000;
    volatile unsigned int* timer = (volatile unsigned int*)0x8000004;

    debug_log("boot\n");

	int id = warp_id();
	debug_log("Warp Id: ");
	debug_hex32((unsigned int)id);
	debug_log("\n");

	terminate();
}