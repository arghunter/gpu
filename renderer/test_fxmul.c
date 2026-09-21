#include "gpu.h"
#include "fx.h"

/* The fx.h validator runs on the host, which compiles the PORTABLE fx_mul.
 * The RISC-V mul/mulh path has never executed on the MALU. This hashes the
 * same deterministic sequence on both targets: matching checksums prove the
 * asm path agrees with the reference, differing ones localise the divergence
 * to the multiplier itself. */

static unsigned int rs = 12345;
static unsigned int rnd(void) { rs ^= rs << 13; rs ^= rs >> 17; rs ^= rs << 5; return rs; }

int main(void) {
    unsigned int hm = 2166136261u, hd = 2166136261u, hs = 2166136261u;
    rs = 12345;
    for (int i = 0; i < 4000; i++) {
        fx a = (fx)rnd(), b = (fx)rnd();
        hm ^= (unsigned int)fx_mul(a, b); hm *= 16777619u;
        fx d = (b == 0) ? 1 : b;
        hd ^= (unsigned int)fx_div(a, d); hd *= 16777619u;
        hs ^= (unsigned int)fx_sqrt((fx)(rnd() & 0x3FFFFFFF)); hs *= 16777619u;
    }
    say("mulsum ", hm);
    say("divsum ", hd);
    say("sqrsum ", hs);

    /* A couple of exact values, so a mismatch says which half is wrong. */
    say("m1     ", (unsigned int)fx_mul(FX(3), FX(5)));          /* 15.0 */
    say("m2     ", (unsigned int)fx_mul(-FX(3), FX(5)));         /* -15.0 */
    say("m3     ", (unsigned int)fx_mul(FX(1000), FX(1000)));    /* 1e6, needs the high word */
    say("m4     ", (unsigned int)fx_mul(FX_HALF, FX_HALF));      /* 0.25 */
    for (;;) __asm__ volatile("nop");
}
