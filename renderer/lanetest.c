#include "gpu.h"
int main(void) {
    int l = laneid();
    putc_((char)('0' + (l & 7)));
    putc_('\n');
    MASKED(1) { putc_('|'); hex_((unsigned)NLANES); putc_('\n'); }
    for (;;) __asm__ volatile("nop");
}
