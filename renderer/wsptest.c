#include "gpu.h"
volatile unsigned int sink[64];
int main(void) {
    if (warpid() == 0) wspawn(4, (void*)0);
    /* Memory traffic so the LSU backs up and the warp actually yields --
     * a warp spinning on ALU ops alone never gives the others a turn. */
    for (int i = 0; i < 200; i++) sink[i & 63] = (unsigned)i;
    MASKED(1) { putc_('W'); putc_((char)('0' + (warpid() & 7))); putc_('\n'); }
    for (int i = 0; i < 2000; i++) sink[i & 63] = (unsigned)i;
    for (;;) __asm__ volatile("nop");
}
