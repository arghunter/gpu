/* Native validation of fx.h. Run on the host, not the GPU: the point is to
 * prove the formats before anything depends on them. */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../fx.h"

static int fails = 0;
static void fail(const char* what, double got, double want, double tol) {
    if (++fails <= 10)
        printf("  FAIL %-22s got %.9f want %.9f (tol %.9f)\n", what, got, want, tol);
}

#define ULP (1.0 / 65536.0)
static double d(fx a) { return (double)a / 65536.0; }

/* xorshift so the run is reproducible */
static unsigned rs = 12345;
static unsigned rnd(void) { rs ^= rs << 13; rs ^= rs >> 17; rs ^= rs << 5; return rs; }
static fx rnd_fx(int mag) { return (fx)(rnd() % (unsigned)(2 * mag * 65536)) - mag * 65536; }

int main(void) {
    printf("fx.h validation\n");

    /* 1. the RISC-V mul/mulh reconstruction must equal the int64 shift */
    double worst_recon = 0;
    for (int i = 0; i < 300000; i++) {
        fx a = (fx)rnd(), b = (fx)rnd();
        long long p = (long long)a * (long long)b;
        fx ref = (fx)(p >> FX_SHIFT);
        int lo = (int)p, hi = (int)(p >> 32);
        fx alt = (fx)(((unsigned)lo >> FX_SHIFT) | ((unsigned)hi << (32 - FX_SHIFT)));
        if (alt != ref) { worst_recon = 1; fail("mul/mulh recon", alt, ref, 0); break; }
    }
    printf("  mul/mulh reconstruction : %s\n", worst_recon ? "MISMATCH" : "exact over 300k pairs");

    /* 2. fx_mul vs real arithmetic */
    double worst_mul = 0;
    for (int i = 0; i < 300000; i++) {
        fx a = rnd_fx(90), b = rnd_fx(90);
        double want = d(a) * d(b), got = d(fx_mul(a, b));
        double e = fabs(got - want);
        if (e > worst_mul) worst_mul = e;
        if (e > ULP) fail("fx_mul", got, want, ULP);
    }
    printf("  fx_mul   max err        : %.9f (%.2f ulp)\n", worst_mul, worst_mul / ULP);

    /* 3. fx_div */
    double worst_div = 0;
    for (int i = 0; i < 200000; i++) {
        fx a = rnd_fx(200), b = rnd_fx(200);
        if (fx_abs(b) < FX_ONE / 64) continue;          /* huge quotients overflow by design */
        double want = d(a) / d(b);
        if (fabs(want) > 20000.0) continue;
        double got = d(fx_div(a, b));
        double e = fabs(got - want);
        if (e > worst_div) worst_div = e;
        if (e > ULP) fail("fx_div", got, want, ULP);
    }
    printf("  fx_div   max err        : %.9f (%.2f ulp)\n", worst_div, worst_div / ULP);
    if (fx_div(FX(1), 0) != FX_MAX) fail("fx_div by zero", fx_div(FX(1),0), FX_MAX, 0);

    /* 4. fx_sqrt */
    double worst_sqrt = 0;
    for (int i = 0; i < 200000; i++) {
        fx a = (fx)(rnd() % 0x40000000u);
        double want = sqrt(d(a)), got = d(fx_sqrt(a));
        double e = fabs(got - want);
        if (e > worst_sqrt) worst_sqrt = e;
        if (e > 2 * ULP) fail("fx_sqrt", got, want, 2 * ULP);
    }
    if (fx_sqrt(0) != 0) fail("fx_sqrt(0)", fx_sqrt(0), 0, 0);
    if (fx_sqrt(-FX_ONE) != 0) fail("fx_sqrt(neg)", fx_sqrt(-FX_ONE), 0, 0);
    if (fx_sqrt(FX(4)) != FX(2)) fail("fx_sqrt(4)", d(fx_sqrt(FX(4))), 2.0, 0);
    printf("  fx_sqrt  max err        : %.9f (%.2f ulp)\n", worst_sqrt, worst_sqrt / ULP);

    /* 5. sin/cos against the true angle -- interpolation should make the
     *    table resolution invisible */
    double worst_sin = 0, worst_cos = 0;
    for (int i = 0; i < 65536; i++) {
        angle_t a = (angle_t)i;
        double th = 2.0 * M_PI * i / 65536.0;
        double es = fabs(d(fx_sin(a)) - sin(th));
        double ec = fabs(d(fx_cos(a)) - cos(th));
        if (es > worst_sin) worst_sin = es;
        if (ec > worst_cos) worst_cos = ec;
        if (es > 4 * ULP) fail("fx_sin", d(fx_sin(a)), sin(th), 4 * ULP);
        if (ec > 4 * ULP) fail("fx_cos", d(fx_cos(a)), cos(th), 4 * ULP);
    }
    printf("  fx_sin   max err        : %.9f (%.2f ulp)\n", worst_sin, worst_sin / ULP);
    printf("  fx_cos   max err        : %.9f (%.2f ulp)\n", worst_cos, worst_cos / ULP);
    if (fx_sin(0) != 0) fail("sin(0)", d(fx_sin(0)), 0, 0);
    if (fx_abs(fx_cos(0) - FX_ONE) > 2) fail("cos(0)", d(fx_cos(0)), 1.0, 0);
    if (fx_abs(fx_sin(ANG_90) - FX_ONE) > 2) fail("sin(90)", d(fx_sin(ANG_90)), 1.0, 0);
    if (fx_abs(fx_cos(ANG_180) + FX_ONE) > 2) fail("cos(180)", d(fx_cos(ANG_180)), -1.0, 0);

    /* 6. conversions and rounding */
    if (FX(3) != 3 * 65536) fail("FX(3)", FX(3), 3 * 65536, 0);
    if (FX_FRAC(1, 2) != 32768) fail("FX_FRAC(1,2)", FX_FRAC(1,2), 32768, 0);
    if (fx_floor_int(FX(-3) - 1) != -4) fail("floor(-3-eps)", fx_floor_int(FX(-3)-1), -4, 0);
    if (fx_round_int(FX(2) + FX_HALF) != 3) fail("round(2.5)", fx_round_int(FX(2)+FX_HALF), 3, 0);
    if (fx_frac(FX(5) + 1234) != 1234) fail("frac", fx_frac(FX(5)+1234), 1234, 0);
    if (fx_clamp(FX(9), FX(0), FX(4)) != FX(4)) fail("clamp hi", 0, 0, 0);
    if (fx_lerp(FX(0), FX(10), FX_HALF) != FX(5)) fail("lerp", d(fx_lerp(FX(0),FX(10),FX_HALF)), 5, 0);

    /* 7. atan2 over the full circle, compared in radians */
    double worst_at = 0;
    for (int i = 0; i < 4000; i++) {
        double th = 2.0 * M_PI * i / 4000.0;
        for (int m = 1; m <= 1000; m *= 10) {
            fx x = (fx)(cos(th) * m * 65536.0), y = (fx)(sin(th) * m * 65536.0);
            if (x == 0 && y == 0) continue;
            angle_t g = fx_atan2(y, x);
            double got = 2.0 * M_PI * g / 65536.0;
            double want = atan2((double)y, (double)x);
            if (want < 0) want += 2.0 * M_PI;
            double e = fabs(got - want);
            if (e > M_PI) e = 2.0 * M_PI - e;
            if (e > worst_at) worst_at = e;
            if (e > 0.002) fail("fx_atan2", got, want, 0.002);
        }
    }
    printf("  fx_atan2 max err        : %.6f rad (%.4f deg)\n", worst_at, worst_at * 180 / M_PI);

    printf(fails ? "\nFAILED (%d)\n" : "\nall checks passed\n", fails);
    return fails != 0;
}
