/* Native validation of vec.h against double-precision references. */
#include <stdio.h>
#include <math.h>
#include "../vec.h"

static int fails = 0;
static double d(fx a) { return (double)a / 65536.0; }
static void chk(const char* what, double got, double want, double tol) {
    if (fabs(got - want) > tol) {
        if (++fails <= 12)
            printf("  FAIL %-26s got %+.6f want %+.6f (tol %.6f)\n", what, got, want, tol);
    }
}
static unsigned rs = 99;
static unsigned rnd(void) { rs ^= rs << 13; rs ^= rs >> 17; rs ^= rs << 5; return rs; }
static fx rnd_fx(int mag) { return (fx)(rnd() % (unsigned)(2u * mag * 65536)) - mag * 65536; }
static vec3 rnd_v3(int mag) { return v3(rnd_fx(mag), rnd_fx(mag), rnd_fx(mag)); }

int main(void) {
    printf("vec.h validation\n");
    double wdot = 0, wcross = 0, wlen = 0, wnorm = 0, wmv = 0, wmm = 0;

    for (int i = 0; i < 100000; i++) {
        vec3 a = rnd_v3(80), b = rnd_v3(80);
        double ax=d(a.x), ay=d(a.y), az=d(a.z), bx=d(b.x), by=d(b.y), bz=d(b.z);

        double e = fabs(d(v3_dot(a,b)) - (ax*bx+ay*by+az*bz));
        if (e > wdot) wdot = e;
        chk("v3_dot", d(v3_dot(a,b)), ax*bx+ay*by+az*bz, 1e-3);

        vec3 c = v3_cross(a,b);
        e = fabs(d(c.x) - (ay*bz-az*by)); if (e > wcross) wcross = e;
        chk("v3_cross.x", d(c.x), ay*bz-az*by, 1e-3);
        chk("v3_cross.y", d(c.y), az*bx-ax*bz, 1e-3);
        chk("v3_cross.z", d(c.z), ax*by-ay*bx, 1e-3);
    }
    printf("  v3_dot     max err : %.7f\n", wdot);
    printf("  v3_cross   max err : %.7f\n", wcross);

    /* length/normalize across magnitudes, exercising the prescale path */
    for (int mag = 1; mag <= 4096; mag *= 4) {
        for (int i = 0; i < 20000; i++) {
            vec3 a = rnd_v3(mag);
            double want = sqrt(d(a.x)*d(a.x) + d(a.y)*d(a.y) + d(a.z)*d(a.z));
            double got = d(v3_length(a));
            double tol = 1e-3 + want * 1e-3;
            double e = fabs(got - want) / (want > 1 ? want : 1);
            if (e > wlen) wlen = e;
            chk("v3_length", got, want, tol);

            if (want > 0.01) {
                vec3 n = v3_normalize(a);
                double nl = sqrt(d(n.x)*d(n.x) + d(n.y)*d(n.y) + d(n.z)*d(n.z));
                double en = fabs(nl - 1.0);
                if (en > wnorm) wnorm = en;
                chk("normalize |n|", nl, 1.0, 2e-3);
            }
        }
    }
    printf("  v3_length  max rel : %.7f  (magnitudes 1..4096)\n", wlen);
    printf("  normalize  max err : %.7f\n", wnorm);

    /* matrix multiply and transform against a double reference */
    for (int i = 0; i < 20000; i++) {
        mat4 A, B, C; double dA[4][4], dB[4][4];
        for (int r = 0; r < 4; r++) for (int c = 0; c < 4; c++) {
            A.m[r][c] = rnd_fx(4); B.m[r][c] = rnd_fx(4);
            dA[r][c] = d(A.m[r][c]); dB[r][c] = d(B.m[r][c]);
        }
        mat4_mul(&C, &A, &B);
        for (int r = 0; r < 4; r++) for (int c = 0; c < 4; c++) {
            double s = 0; for (int k = 0; k < 4; k++) s += dA[r][k]*dB[k][c];
            double e = fabs(d(C.m[r][c]) - s); if (e > wmm) wmm = e;
            chk("mat4_mul", d(C.m[r][c]), s, 1e-3);
        }
        vec4 v = v4(rnd_fx(8), rnd_fx(8), rnd_fx(8), FX_ONE);
        vec4 t = mat4_mul_v4(&A, v);
        double dv[4] = { d(v.x), d(v.y), d(v.z), d(v.w) };
        double want0 = dA[0][0]*dv[0]+dA[0][1]*dv[1]+dA[0][2]*dv[2]+dA[0][3]*dv[3];
        double e = fabs(d(t.x) - want0); if (e > wmv) wmv = e;
        chk("mat4_mul_v4", d(t.x), want0, 1e-3);
    }
    printf("  mat4_mul   max err : %.7f\n", wmm);
    printf("  mat4_mul_v4 max err: %.7f\n", wmv);

    /* aliasing: mat4_mul(&A,&A,&B) must behave like a temp */
    { mat4 A, B, R, S;
      for (int r=0;r<4;r++) for (int c=0;c<4;c++){A.m[r][c]=rnd_fx(2);B.m[r][c]=rnd_fx(2);}
      S = A; mat4_mul(&R,&A,&B); mat4_mul(&S,&S,&B);
      for (int r=0;r<4;r++) for (int c=0;c<4;c++)
          chk("mat4_mul aliased", d(S.m[r][c]), d(R.m[r][c]), 0); }

    /* rotations act the way their names claim */
    { mat4 M; vec3 r;
      mat4_rot_z(&M, ANG_90); r = mat4_mul_dir(&M, v3(FX_ONE,0,0));
      chk("rotZ90 x->y .x", d(r.x), 0.0, 1e-3); chk("rotZ90 x->y .y", d(r.y), 1.0, 1e-3);
      mat4_rot_x(&M, ANG_90); r = mat4_mul_dir(&M, v3(0,FX_ONE,0));
      chk("rotX90 y->z .y", d(r.y), 0.0, 1e-3); chk("rotX90 y->z .z", d(r.z), 1.0, 1e-3);
      mat4_rot_y(&M, ANG_90); r = mat4_mul_dir(&M, v3(0,0,FX_ONE));
      chk("rotY90 z->x .z", d(r.z), 0.0, 1e-3); chk("rotY90 z->x .x", d(r.x), 1.0, 1e-3); }

    /* A rigid transform times its inverse is the identity. The residual is
     * dominated by translation magnitude times the orthonormality error of
     * the composed rotation (~2e-4 from sin/cos), so the translation column
     * is checked against a magnitude-scaled tolerance rather than an
     * absolute one -- at 50 units that is 1e-4 relative, far under a pixel. */
    double wrot = 0, wtrn = 0;
    for (int i = 0; i < 2000; i++) {
        mat4 R, T, M, I, P;
        mat4_rot_y(&R, (angle_t)rnd());
        mat4_rot_x(&T, (angle_t)rnd());
        mat4_mul(&R, &R, &T);
        vec3 p = rnd_v3(50);
        mat4_translate(&T, p);
        mat4_mul(&M, &T, &R);
        mat4_rigid_inverse(&I, &M);
        mat4_mul(&P, &M, &I);
        double plen = sqrt(d(p.x)*d(p.x)+d(p.y)*d(p.y)+d(p.z)*d(p.z));
        for (int r = 0; r < 4; r++) for (int c = 0; c < 4; c++) {
            double want = (r == c) ? 1.0 : 0.0, got = d(P.m[r][c]);
            double e = fabs(got - want);
            if (c == 3 && r < 3) { if (e > wtrn) wtrn = e; chk("M*inv(M) trans", got, want, 1e-3 + plen*4e-4); }
            else                 { if (e > wrot) wrot = e; chk("M*inv(M) rot",   got, want, 1e-3); }
        }
    }
    printf("  M*inv(M) rot  max err: %.7f\n", wrot);
    printf("  M*inv(M) tran max err: %.7f  (|t| up to 86)\n", wtrn);

    printf(fails ? "\nFAILED (%d)\n" : "\nall checks passed\n", fails);
    return fails != 0;
}
