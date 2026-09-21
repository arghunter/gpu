#ifndef FX_H
#define FX_H

/* Q16.16 fixed point.
 *
 * Range +/-32767.99998, resolution 1/65536. This is the format for world,
 * view and object space. Rasterisation uses Q28.4 screen coordinates and
 * depth uses Q0.30 reciprocal-w -- those are deliberately NOT this type, and
 * mixing them is what produced the overflow in the previous renderer. Each
 * quantity's format is stated where it is declared. */

typedef int fx;

#define FX_SHIFT 16
#define FX_ONE   ((fx)(1 << FX_SHIFT))
#define FX_HALF  ((fx)(1 << (FX_SHIFT - 1)))
#define FX_MAX   ((fx)0x7FFFFFFF)
#define FX_MIN   ((fx)0x80000000)

/* Integer -> fx. Overflows silently above 32767; that ceiling is the reason
 * screen-space work uses its own format. */
#define FX(i)         ((fx)((int)(i) * FX_ONE))
/* Multiply rather than shift: shifting a negative value left is undefined
 * behaviour, and a host/target disagreement there would be near-impossible
 * to localise from a rendered image. */
#define FX_FRAC(n, d) ((fx)(((long long)(n) * FX_ONE) / (d)))

static inline int fx_floor_int(fx a) { return a >> FX_SHIFT; }          /* floor, not trunc */
static inline int fx_round_int(fx a) { return (a + FX_HALF) >> FX_SHIFT; }
static inline fx  fx_frac(fx a)      { return a & (FX_ONE - 1); }

static inline fx fx_abs(fx a)              { return a < 0 ? -a : a; }
static inline fx fx_min(fx a, fx b)        { return a < b ? a : b; }
static inline fx fx_max(fx a, fx b)        { return a > b ? a : b; }
static inline fx fx_clamp(fx v, fx lo, fx hi) { return v < lo ? lo : (v > hi ? hi : v); }

/* The 64-bit intermediate is mandatory: a*b overflows 32 bits for operands
 * as small as 256.0. RV32IM computes both halves in two instructions, so
 * this costs no more than a naive 32-bit multiply would have. */
#if defined(__riscv) && !defined(FX_PORTABLE)
static inline fx fx_mul(fx a, fx b) {
    int lo, hi;
    __asm__("mul %0,%2,%3\n\tmulh %1,%2,%3" : "=&r"(lo), "=r"(hi) : "r"(a), "r"(b));
    return (fx)(((unsigned)lo >> FX_SHIFT) | ((unsigned)hi << (32 - FX_SHIFT)));
}
#else
static inline fx fx_mul(fx a, fx b) {
    return (fx)(((long long)a * (long long)b) >> FX_SHIFT);
}
#endif

/* Exact, but a 64/32 divide -- on RV32 this is a __divdi3 call, and the
 * hardware divider stalls the whole pipeline while it runs. Per-vertex and
 * per-span use only; never per pixel. */
static inline fx fx_div(fx a, fx b) {
    if (b == 0) return a < 0 ? FX_MIN : FX_MAX;
    return (fx)((((long long)a) << FX_SHIFT) / b);
}

/* Q16.16 square root by restoring digit-by-digit. Negative input clamps to 0
 * rather than trapping, since it only ever arises from rounding a length
 * that should have been zero. */
static inline fx fx_sqrt(fx a) {
    if (a <= 0) return 0;
    unsigned long long v = (unsigned long long)(unsigned)a << FX_SHIFT;
    unsigned long long rem = 0, root = 0;
    for (int i = 0; i < 32; i++) {
        root <<= 1;
        rem = (rem << 2) | (v >> 62);
        v <<= 2;
        if (root < rem) { rem -= root + 1; root += 2; }
    }
    return (fx)(root >> 1);
}

static inline fx fx_lerp(fx a, fx b, fx t) { return a + fx_mul(b - a, t); }

/* Binary angles: 65536 counts to the full turn, so wrapping is free and
 * there is no pi to round. */
typedef unsigned short angle_t;

#define ANG_360 0x10000
#define ANG_180 0x8000
#define ANG_90  0x4000
#define ANG_45  0x2000
#define ANG_FROM_DEG(d) ((angle_t)(((long long)(d) * ANG_360) / 360))

#define SINTAB_BITS 10
#define SINTAB_SIZE (1 << SINTAB_BITS)
extern const fx fx_sintab[SINTAB_SIZE];

/* Linearly interpolated between table entries. Truncating to the nearest
 * entry would cap angular resolution at one step (2*pi/1024 = 0.35 degrees),
 * which is coarse enough to see as stepping when the camera turns slowly.
 * Interpolation drops the error to well under an ulp for the cost of one
 * multiply -- irrelevant here because these are called per frame, not per
 * pixel. Do not call them per pixel. */
static inline fx fx_sin(angle_t a) {
    unsigned idx = (unsigned)a >> (16 - SINTAB_BITS);
    fx t  = (fx)(((unsigned)a & ((1u << (16 - SINTAB_BITS)) - 1)) << SINTAB_BITS);
    fx s0 = fx_sintab[idx & (SINTAB_SIZE - 1)];
    fx s1 = fx_sintab[(idx + 1) & (SINTAB_SIZE - 1)];
    return s0 + fx_mul(s1 - s0, t);
}
static inline fx fx_cos(angle_t a) {
    return fx_sin((angle_t)(a + ANG_90));
}

/* atan2 in binary angles.
 *
 * Polynomial rather than a table: atan is only wanted for look_at and input
 * handling, a handful of calls per frame, and a table would need its own
 * octant folding anyway. Coefficients are a least-squares fit of
 * atan(r)/r on [0,1]; the validator pins the actual error. */
static inline fx fx_atan_unit(fx r) {           /* r in [0,1] -> radians Q16.16 */
    fx r2 = fx_mul(r, r);
    fx t  = 5199;                               /*  0.079331 */
    t = fx_mul(t, r2) - 18919;                  /* -0.288679 */
    t = fx_mul(t, r2) + 65231;                  /*  0.995354 */
    return fx_mul(t, r);
}

/* 1/(2*pi) in Q16.16. Multiplying radians by this yields the fraction of a
 * turn, which in Q16.16 *is* the binary angle -- a full turn is 65536 in
 * both representations, so no second scaling step is needed. */
#define FX_INV_TAU 10430

static inline angle_t fx_atan2(fx y, fx x) {
    if (x == 0 && y == 0) return 0;
    fx ax = fx_abs(x), ay = fx_abs(y);
    angle_t a;
    if (ax >= ay) a = (angle_t)fx_mul(fx_atan_unit(fx_div(ay, ax)), FX_INV_TAU);
    else          a = (angle_t)(ANG_90 - fx_mul(fx_atan_unit(fx_div(ax, ay)), FX_INV_TAU));
    if (x < 0) a = (angle_t)(ANG_180 - a);
    if (y < 0) a = (angle_t)(-(int)a);
    return a;
}

#endif /* FX_H */
