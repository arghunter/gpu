/* Native validation of camera.h/.c: conventions, view matrix, projection. */
#include <stdio.h>
#include <math.h>
#include "../camera.h"

static int fails = 0;
static double d(fx a) { return (double)a / 65536.0; }
static void chk(const char* what, double got, double want, double tol) {
    if (fabs(got - want) > tol && ++fails <= 12)
        printf("  FAIL %-28s got %+.6f want %+.6f (tol %.5f)\n", what, got, want, tol);
}
static unsigned rs = 7; static unsigned rnd(void){rs^=rs<<13;rs^=rs>>17;rs^=rs<<5;return rs;}
static fx rnd_fx(int m){return (fx)(rnd()%(unsigned)(2u*m*65536))-m*65536;}

int main(void) {
    camera_t c; cam_init(&c, 320, 240);
    printf("camera validation\n");

    /* 1. default pose looks down -Z, right is +X, up is +Y */
    { vec3 r,u,f; cam_basis(&c,&r,&u,&f);
      chk("default fwd.z", d(f.z), -1.0, 1e-3); chk("default fwd.x", d(f.x), 0.0, 1e-3);
      chk("default right.x", d(r.x), 1.0, 1e-3); chk("default up.y", d(u.y), 1.0, 1e-3); }

    /* 2. yaw of a quarter turn swings forward to -X (CCW seen from above) */
    { camera_t t = c; t.yaw = ANG_90; vec3 f; cam_basis(&t,0,0,&f);
      chk("yaw90 fwd.x", d(f.x), -1.0, 2e-3); chk("yaw90 fwd.z", d(f.z), 0.0, 2e-3); }

    /* 3. positive pitch looks up */
    { camera_t t = c; t.pitch = ANG_FROM_DEG(30); vec3 f; cam_basis(&t,0,0,&f);
      chk("pitch30 fwd.y", d(f.y), 0.5, 3e-3); }

    /* 4. the view matrix takes the eye to the origin and fwd to -Z */
    for (int i = 0; i < 4000; i++) {
        camera_t t = c;
        t.pos = v3(rnd_fx(60), rnd_fx(60), rnd_fx(60));
        t.yaw = (angle_t)rnd(); t.pitch = (angle_t)(rnd() % ANG_90) - ANG_45;
        mat4 V; cam_view(&t, &V);
        vec4 o = mat4_mul_point(&V, t.pos);
        double tol = 1e-2;
        chk("view(eye).x", d(o.x), 0.0, tol);
        chk("view(eye).y", d(o.y), 0.0, tol);
        chk("view(eye).z", d(o.z), 0.0, tol);

        vec3 f; cam_basis(&t,0,0,&f);
        vec3 ahead = v3_add(t.pos, v3_scale(f, FX(10)));
        vec4 a = mat4_mul_point(&V, ahead);
        chk("view(ahead).x", d(a.x), 0.0, 3e-2);
        chk("view(ahead).y", d(a.y), 0.0, 3e-2);
        chk("view(ahead).z", d(a.z), -10.0, 5e-2);
    }

    /* 5. look_at aims the camera at the target */
    for (int i = 0; i < 4000; i++) {
        camera_t t = c;
        t.pos = v3(rnd_fx(40), rnd_fx(40), rnd_fx(40));
        vec3 tgt = v3(rnd_fx(40), rnd_fx(40), rnd_fx(40));
        vec3 dir = v3_sub(tgt, t.pos);
        if (v3_length(dir) < FX(2)) continue;
        cam_look_at(&t, tgt);
        vec3 f; cam_basis(&t,0,0,&f);
        vec3 want = v3_normalize(dir);
        double dot = d(f.x)*d(want.x) + d(f.y)*d(want.y) + d(f.z)*d(want.z);
        chk("look_at alignment", dot, 1.0, 3e-3);
    }

    /* 6. projection maps the near and far planes to NDC -1 and +1 */
    { mat4 P; cam_proj(&c, &P);
      vec4 n = mat4_mul_point(&P, v3(0,0,-c.znear));
      vec4 f = mat4_mul_point(&P, v3(0,0,-c.zfar));
      chk("ndc z at znear", d(n.z)/d(n.w), -1.0, 3e-3);
      chk("ndc z at zfar",  d(f.z)/d(f.w),  1.0, 3e-3);
      /* w must equal view depth: that is what 1/w depth relies on */
      chk("clip.w == -z", d(n.w), d(c.znear), 1e-3); }

    /* 7. a point on the vertical fov edge lands exactly on the NDC edge */
    { mat4 P; cam_proj(&c, &P);
      double half = tan(M_PI * 60.0 / 360.0);
      fx z = FX(10);
      vec4 e = mat4_mul_point(&P, v3(0, (fx)(half*10*65536), -z));
      chk("ndc y at fov edge", d(e.y)/d(e.w), 1.0, 5e-3); }

    /* 8. move_local walks along the camera axes */
    { camera_t t = c; t.yaw = ANG_90;
      cam_move_local(&t, v3(0,0,FX(5)));
      vec3 f; cam_basis(&t,0,0,&f);
      chk("move fwd .x", d(t.pos.x), -5.0, 2e-2); chk("move fwd .z", d(t.pos.z), 0.0, 2e-2); }

    printf(fails ? "\nFAILED (%d)\n" : "\nall checks passed\n", fails);
    return fails != 0;
}
