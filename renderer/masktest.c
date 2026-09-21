#include "gpu.h"
int main(void) {
    putc_('A'); putc_('\n');
    MASKED(1) { putc_('B'); }
    putc_('\n'); putc_('C'); putc_('\n');
    int full = tmc(-1); tmc(full);
    putc_('D'); putc_('\n');
    MASKED(0) { putc_('X'); }          /* empty mask: must still restore */
    putc_('E'); putc_('\n');
    for (;;) __asm__ volatile("nop");
}
