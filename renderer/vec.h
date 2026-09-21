#ifndef VEC_H
#define VEC_H

#include "fx.h"

/* Vectors and 4x4 matrices in Q16.16.
 *
 * Convention: column vectors, v' = M * v, with row-major storage so m[r][c]
 * is row r column c. Translation therefore lives in m[0..2][3].
 *
 * mat4 is 64 bytes, so it is always passed by pointer; vec3/vec4 go by value
 * and stay in registers under the RV32 ABI. */

typedef struct { fx x, y, z; }       vec3;
typedef struct { fx x, y, z, w; }    vec4;
typedef struct { fx m[4][4]; }       mat4;

static inline vec3 v3(fx x, fx y, fx z)        { vec3 r = {x, y, z};    return r; }
static inline vec4 v4(fx x, fx y, fx z, fx w)  { vec4 r = {x, y, z, w}; return r; }
static inline vec4 v3_to_v4(vec3 a, fx w)      { return v4(a.x, a.y, a.z, w); }
static inline vec3 v4_to_v3(vec4 a)            { return v3(a.x, a.y, a.z); }

static inline vec3 v3_add(vec3 a, vec3 b)  { return v3(a.x+b.x, a.y+b.y, a.z+b.z); }
static inline vec3 v3_sub(vec3 a, vec3 b)  { return v3(a.x-b.x, a.y-b.y, a.z-b.z); }
static inline vec3 v3_neg(vec3 a)          { return v3(-a.x, -a.y, -a.z); }
static inline vec3 v3_scale(vec3 a, fx s)  { return v3(fx_mul(a.x,s), fx_mul(a.y,s), fx_mul(a.z,s)); }

/* Overflows for operands beyond about 181.0, since 181^2 just fits Q16.16.
 * v3_length and v3_normalize pre-scale to stay clear of that; a raw dot of
 * two large vectors does not. */
static inline fx v3_dot(vec3 a, vec3 b) {
    return fx_mul(a.x,b.x) + fx_mul(a.y,b.y) + fx_mul(a.z,b.z);
}

static inline vec3 v3_cross(vec3 a, vec3 b) {
    return v3(fx_mul(a.y,b.z) - fx_mul(a.z,b.y),
              fx_mul(a.z,b.x) - fx_mul(a.x,b.z),
              fx_mul(a.x,b.y) - fx_mul(a.y,b.x));
}

/* Scale the vector so its largest component lands in [0.5, 1.0] before
 * squaring, and report the shift so callers can undo it.
 *
 * Scaling only downward is not enough: a component of 0.01 squares to 6.5 in
 * Q16.16 and truncates to 6, a 15% error that survives the sqrt. Small
 * vectors must be shifted UP. Shifting left is lossless, and the guard keeps
 * the largest component below 1.0 so the squares cannot overflow.
 *
 * Returns a signed shift; positive means the vector was shifted left. */
static inline fx fx_shl(fx v, int sh) {
    return sh >= 0 ? (fx)((unsigned)v << sh) : (fx)(v >> (-sh));
}

static inline int v3_scale_shift(vec3 a) {
    fx m = fx_max(fx_max(fx_abs(a.x), fx_abs(a.y)), fx_abs(a.z));
    if (m <= 0) return 0;
    int sh = 0;
    while (m > FX_ONE)        { m >>= 1; sh--; }
    while (m < (FX_ONE >> 1)) { m <<= 1; sh++; }
    return sh;
}

static inline fx v3_length(vec3 a) {
    int sh = v3_scale_shift(a);
    vec3 t = v3(fx_shl(a.x,sh), fx_shl(a.y,sh), fx_shl(a.z,sh));
    fx l = fx_sqrt(fx_mul(t.x,t.x) + fx_mul(t.y,t.y) + fx_mul(t.z,t.z));
    return fx_shl(l, -sh);
}

/* Scale-invariant, so the prescale costs nothing here beyond the shifts. */
static inline vec3 v3_normalize(vec3 a) {
    int sh = v3_scale_shift(a);
    vec3 t = v3(fx_shl(a.x,sh), fx_shl(a.y,sh), fx_shl(a.z,sh));
    fx l = fx_sqrt(fx_mul(t.x,t.x) + fx_mul(t.y,t.y) + fx_mul(t.z,t.z));
    if (l == 0) return v3(0,0,0);
    return v3(fx_div(t.x,l), fx_div(t.y,l), fx_div(t.z,l));
}

static inline vec3 v3_lerp(vec3 a, vec3 b, fx t) {
    return v3(fx_lerp(a.x,b.x,t), fx_lerp(a.y,b.y,t), fx_lerp(a.z,b.z,t));
}

/* ---- matrices --------------------------------------------------------- */

static inline void mat4_identity(mat4* o) {
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            o->m[r][c] = (r == c) ? FX_ONE : 0;
}

/* out = a * b. Aliasing-safe: accumulates into a local. */
static inline void mat4_mul(mat4* o, const mat4* a, const mat4* b) {
    mat4 t;
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++) {
            fx s = 0;
            for (int k = 0; k < 4; k++) s += fx_mul(a->m[r][k], b->m[k][c]);
            t.m[r][c] = s;
        }
    *o = t;
}

static inline vec4 mat4_mul_v4(const mat4* a, vec4 v) {
    return v4(fx_mul(a->m[0][0],v.x) + fx_mul(a->m[0][1],v.y) + fx_mul(a->m[0][2],v.z) + fx_mul(a->m[0][3],v.w),
              fx_mul(a->m[1][0],v.x) + fx_mul(a->m[1][1],v.y) + fx_mul(a->m[1][2],v.z) + fx_mul(a->m[1][3],v.w),
              fx_mul(a->m[2][0],v.x) + fx_mul(a->m[2][1],v.y) + fx_mul(a->m[2][2],v.z) + fx_mul(a->m[2][3],v.w),
              fx_mul(a->m[3][0],v.x) + fx_mul(a->m[3][1],v.y) + fx_mul(a->m[3][2],v.z) + fx_mul(a->m[3][3],v.w));
}

/* Point: w = 1, translation applies. Direction: w = 0, it does not. */
static inline vec4 mat4_mul_point(const mat4* a, vec3 p) { return mat4_mul_v4(a, v3_to_v4(p, FX_ONE)); }
static inline vec3 mat4_mul_dir(const mat4* a, vec3 d)   { return v4_to_v3(mat4_mul_v4(a, v3_to_v4(d, 0))); }

static inline void mat4_translate(mat4* o, vec3 t) {
    mat4_identity(o);
    o->m[0][3] = t.x; o->m[1][3] = t.y; o->m[2][3] = t.z;
}

static inline void mat4_scale(mat4* o, vec3 s) {
    mat4_identity(o);
    o->m[0][0] = s.x; o->m[1][1] = s.y; o->m[2][2] = s.z;
}

static inline void mat4_rot_x(mat4* o, angle_t a) {
    fx s = fx_sin(a), c = fx_cos(a);
    mat4_identity(o);
    o->m[1][1] =  c; o->m[1][2] = -s;
    o->m[2][1] =  s; o->m[2][2] =  c;
}
static inline void mat4_rot_y(mat4* o, angle_t a) {
    fx s = fx_sin(a), c = fx_cos(a);
    mat4_identity(o);
    o->m[0][0] =  c; o->m[0][2] =  s;
    o->m[2][0] = -s; o->m[2][2] =  c;
}
static inline void mat4_rot_z(mat4* o, angle_t a) {
    fx s = fx_sin(a), c = fx_cos(a);
    mat4_identity(o);
    o->m[0][0] =  c; o->m[0][1] = -s;
    o->m[1][0] =  s; o->m[1][1] =  c;
}

/* Inverse of a rigid transform (rotation + translation): transpose the 3x3
 * and re-derive the translation. Much better conditioned in fixed point than
 * a general inverse, and it is all a camera ever needs. */
static inline void mat4_rigid_inverse(mat4* o, const mat4* a) {
    mat4 t;
    mat4_identity(&t);
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++) t.m[r][c] = a->m[c][r];
    vec3 p = v3(a->m[0][3], a->m[1][3], a->m[2][3]);
    t.m[0][3] = -(fx_mul(t.m[0][0],p.x) + fx_mul(t.m[0][1],p.y) + fx_mul(t.m[0][2],p.z));
    t.m[1][3] = -(fx_mul(t.m[1][0],p.x) + fx_mul(t.m[1][1],p.y) + fx_mul(t.m[1][2],p.z));
    t.m[2][3] = -(fx_mul(t.m[2][0],p.x) + fx_mul(t.m[2][1],p.y) + fx_mul(t.m[2][2],p.z));
    *o = t;
}

#endif /* VEC_H */
