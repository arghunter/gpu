#include <stdint.h>
#include "llm_model.h"

/* ------------------------------------------------------------------ settings (edit here) */
#ifndef TEMP_PERCENT
#define TEMP_PERCENT 80              /* temperature x100; 0 = always the likeliest token */
#endif
#ifndef SEED
#define SEED 0                       /* 0 = from the timer */
#endif
#ifndef STEPS
#define STEPS (SEQ_LEN < 256 ? SEQ_LEN : 256)   /* max tokens per story */
#endif
#ifndef SELFTEST_STEPS
#define SELFTEST_STEPS 2             /* tokens checked at boot; 0 = skip */
#endif
#ifndef USE_FRAMEBUFFER
#define USE_FRAMEBUFFER 1            /* draw on the screen */
#endif
#ifndef VISUALIZE
#define VISUALIZE 1                  /* live view of the model under the story */
#endif
#if !USE_FRAMEBUFFER
#undef VISUALIZE
#define VISUALIZE 0
#endif
#define TITLE "TinyStories on our GPU: int8, no floats"
#ifndef MAX_STORIES
#define MAX_STORIES 0                /* 0 = forever */
#endif

/* ------------------------------------------------------------------ hardware addresses */
#ifndef STACK_TOP
#define STACK_TOP     0x8000000
#endif
#ifndef UART_ADDR
#define UART_ADDR     0x8000034
#endif
#ifndef SIM_UART_ADDR
#define SIM_UART_ADDR 0x70000000     /* simulator console */
#endif
#ifndef TIMER_ADDR
#define TIMER_ADDR    0x8000004      /* microseconds */
#endif
#ifndef FB_ADDR
#define FB_ADDR       0x10000000     /* 320x240 pixels, 0x00RRGGBB */
#endif

#if STEPS > SEQ_LEN
#error "STEPS must be <= SEQ_LEN"
#endif
#if SELFTEST_STEPS > GOLDEN_STEPS || SELFTEST_STEPS > STEPS
#error "SELFTEST_STEPS must be <= GOLDEN_STEPS (from llm_model.h) and <= STEPS"
#endif

#define STR_(x) #x
#define STR(x) STR_(x)
#ifdef HOST_TEST
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static unsigned int host_fb[320 * 240];
#define FRAMEBUFFER ((volatile unsigned int *)host_fb)
static void uart_putc(char c) { putchar((unsigned char)c); fflush(stdout); }
static unsigned int read_timer(void) {
    return (unsigned int)((unsigned long long)clock() * 1000000ull / CLOCKS_PER_SEC);
}
#else
/* Entry point at address 0: set gp and sp, call main. The pragma keeps _start first in .text. */
__asm__(".pushsection .text\n"
        ".globl _start\n"
        ".weak __global_pointer$\n"
        "_start:\n"
        ".option push\n"
        ".option norelax\n"
        "lui gp, %hi(__global_pointer$)\n"
        "addi gp, gp, %lo(__global_pointer$)\n"
        ".option pop\n"
        "li sp, " STR(STACK_TOP) "\n"
        "call main\n"
        "1: j 1b\n"
        ".popsection\n");
#pragma GCC optimize("no-reorder-functions")
#define FRAMEBUFFER ((volatile unsigned int *)FB_ADDR)
static void uart_putc(char c) {
    *((volatile unsigned int *)SIM_UART_ADDR) = (unsigned char)c;
    *((volatile unsigned char *)UART_ADDR) = (unsigned char)c;
}
static unsigned int read_timer(void) { return *((volatile unsigned int *)TIMER_ADDR); }
/* gcc may emit calls to these; volatile stops them compiling into calls to themselves */
void *memset(void *d, int c, __SIZE_TYPE__ n) {
    volatile unsigned char *p = d;
    while (n--) *p++ = (unsigned char)c;
    return d;
}
void *memcpy(void *d, const void *s, __SIZE_TYPE__ n) {
    volatile unsigned char *p = d;
    const unsigned char *q = s;
    while (n--) *p++ = *q++;
    return d;
}
void *memmove(void *d, const void *s, __SIZE_TYPE__ n) {
    volatile unsigned char *p = d;
    const unsigned char *q = s;
    if (p < q) { while (n--) *p++ = *q++; }
    else { p += n; q += n; while (n--) *--p = *--q; }
    return d;
}
int memcmp(const void *a, const void *b, __SIZE_TYPE__ n) {
    const volatile unsigned char *p = a, *q = b;
    for (; n; n--, p++, q++) if (*p != *q) return *p < *q ? -1 : 1;
    return 0;
}
#endif

/* ------------------------------------------------------------------ debug output */
void debug_log(char *s) { while (*s) uart_putc(*s++); }

static void debug_hex32(unsigned int value) {
    static const char hex[] = "0123456789ABCDEF";
    for (int i = 7; i >= 0; i--) uart_putc(hex[(value >> (i * 4)) & 0xF]);
}

static void debug_dec(unsigned int v) {
    char buf[10];
    int n = 0;
    do { buf[n++] = (char)('0' + v % 10); v /= 10; } while (v);
    while (n) uart_putc(buf[--n]);
}

static void trace(char *label, unsigned int value) {
    debug_log(label);
    debug_hex32(value);
    debug_log("\n");
}

/* ------------------------------------------------------------------ model data */
#define model_blob ((const uint8_t *)model_words)
#define I8(off)  ((const int8_t *)(model_blob + (off)))
#define I32(off) ((const int32_t *)(model_blob + (off)))
#define U32(off) ((const uint32_t *)(model_blob + (off)))

#if SHARED_CLASSIFIER
#define OFF_CLS   OFF_TOK_EMB
#define OFF_CLS_M OFF_TOK_EMB_M
#define OFF_CLS_E OFF_TOK_EMB_E
#else
#define OFF_CLS   OFF_WCLS
#define OFF_CLS_M OFF_WCLS_M
#define OFF_CLS_E OFF_WCLS_E
#endif

/* ------------------------------------------------------------------ state */
#define MAXV(a, b) ((a) > (b) ? (a) : (b))
static int32_t x[DIM];                         /* residual stream, Q16 */
static int32_t xb[DIM], xb2[DIM], qv[DIM];
static int32_t hb[HIDDEN_DIM], hb2[HIDDEN_DIM];
static int32_t tmp[DIM];
static int8_t act[MAXV(DIM, HIDDEN_DIM)];      /* int8 input of the next matmul */
static int32_t att[SEQ_LEN];
static int32_t logits[VOCAB_SIZE];
static int32_t key_cache[N_LAYERS * STEPS * KV_DIM];
static int32_t value_cache[N_LAYERS * STEPS * KV_DIM];
static uint32_t rng_state;

#if VISUALIZE                                  /* captured during forward() for the screen */
#define VIZ_HIST 32                            /* tokens in the attention panel */
#ifndef VIZ_ATT_LAYER
#define VIZ_ATT_LAYER (N_LAYERS - 1)           /* layer whose attention is shown */
#endif
static int32_t viz_x[N_LAYERS + 1][DIM];       /* after the embedding and each layer */
static int32_t viz_att[N_HEADS][VIZ_HIST];     /* Q16; -1 = no token yet */
static int viz_att_on;
#define VIZ_KEEP_X(r) do { for (int i_ = 0; i_ < DIM; i_++) viz_x[r][i_] = x[i_]; } while (0)
#define VIZ_ATT_SELECT(l) (viz_att_on = ((l) == VIZ_ATT_LAYER))
#else
#define VIZ_KEEP_X(r) ((void)0)
#define VIZ_ATT_SELECT(l) ((void)0)
#endif

/* ------------------------------------------------------------------ integer helpers */
static int bitlen32(uint32_t v) { int n = 0; while (v) { v >>= 1; n++; } return n; }
static int bitlen64(uint64_t v) {
    uint32_t hi = (uint32_t)(v >> 32);
    return hi ? 32 + bitlen32(hi) : bitlen32((uint32_t)v);
}
static int32_t sat32(int64_t v) { return v > INT32_MAX ? INT32_MAX : v < INT32_MIN ? INT32_MIN : (int32_t)v; }
static int32_t clampq(int32_t v, int32_t lim) { return v > lim ? lim : v < -lim ? -lim : v; }

/* p * 2^-sh, rounded to nearest, saturated to int32 */
static int32_t requant(int64_t p, int sh) {
    if (sh > 0) {
        if (sh > 62) return 0;
        return sat32((p + ((int64_t)1 << (sh - 1))) >> sh);
    }
    if (sh < 0) {
        int64_t v = sat32(p);
        if (-sh > 31) return v > 0 ? INT32_MAX : v < 0 ? INT32_MIN : 0;
        return sat32(v * ((int64_t)1 << -sh));
    }
    return sat32(p);
}

static uint32_t isqrt32(uint32_t v) {           /* floor(sqrt(v)) */
    uint32_t r = 0, bit = 1u << 30;
    while (bit > v) bit >>= 2;
    while (bit) {
        if (v >= r + bit) { v -= r + bit; r = (r >> 1) + bit; }
        else r >>= 1;
        bit >>= 2;
    }
    return r;
}

/* exp(x) in Q30 for x <= 0 in Q16, from a 2^-x table */
static int32_t exp_q30(int32_t xq16) {
    if (xq16 >= 0) return 1 << 30;
    if (xq16 <= -EXP_CUTOFF_Q16) return 0;
    const int32_t *lut = I32(OFF_POW2_LUT);
    int64_t y = ((int64_t)(-xq16) * LOG2E_Q30 + (1 << 29)) >> 30;
    int32_t z = (int32_t)(y >> 16), f = (int32_t)(y & 0xFFFF);
    int32_t a = lut[f >> 8], b = lut[(f >> 8) + 1];
    int32_t v = a - (((a - b) * (f & 0xFF) + 128) >> 8);
    if (z >= 31) return 0;
    return z == 0 ? v : (v + (1 << (z - 1))) >> z;
}

/* ------------------------------------------------------------------ core ops */

/* int32 vector (frac fractional bits) -> int8 + scale (m, e): real ~= q * m * 2^-e */
static void quantize(int8_t *q, const int32_t *v, int n, int frac, int32_t *m, int32_t *e) {
    uint32_t M = 0;
    for (int i = 0; i < n; i++) {
        uint32_t a = v[i] < 0 ? 0u - (uint32_t)v[i] : (uint32_t)v[i];
        if (a > M) M = a;
    }
    int s = M ? bitlen32(M) - 15 : 0;
    int32_t Mp = s >= 0 ? (int32_t)(M >> s) : (int32_t)(M << -s);
    int32_t R = M ? (127 << 22) / Mp : 0;
    for (int i = 0; i < n; i++) {
        int32_t vp = s >= 0 ? v[i] >> s : v[i] * (1 << -s);
        int32_t t = (vp * R + (1 << 21)) >> 22;
        q[i] = (int8_t)(t > 127 ? 127 : t < -127 ? -127 : t);
    }
    *m = M ? (Mp << 7) / 127 : 0;
    *e = M ? 7 - s + frac : 0;
}

/* RMSNorm(x) * g, output as int8 + scale */
static void rmsnorm_quant(int8_t *q, int32_t *qm, int32_t *qe,
                          const int32_t *xin, const int32_t *g, int gf, int n) {
    uint32_t M = 0;
    for (int i = 0; i < n; i++) {
        uint32_t a = xin[i] < 0 ? 0u - (uint32_t)xin[i] : (uint32_t)xin[i];
        if (a > M) M = a;
    }
    if (M == 0) { quantize(q, xin, n, 0, qm, qe); return; }
    int kx = bitlen32(M) - 15;
    uint64_t ss = 0;
    for (int i = 0; i < n; i++) {
        int32_t xs = kx >= 0 ? xin[i] >> kx : xin[i] * (1 << -kx);
        tmp[i] = xs * g[i];
        ss += (uint64_t)((int64_t)xs * xs);
    }
    int t = bitlen64(ss) - 31;
    if (t < 0) t = 0;
    t += t & 1;
    uint32_t ms = (uint32_t)(ss >> t) / (uint32_t)n;
    int es = 24 + t + 2 * kx;
    uint64_t eps = es > 63 ? 0 : es >= 0 ? (EPS_Q56 >> es) : (EPS_Q56 << -es);
    uint64_t A = (uint64_t)ms + eps;
    int j = (bitlen64(A) - 29) >> 1;
    uint32_t Ap = (uint32_t)(j >= 0 ? A >> (2 * j) : A << (-2 * j));
    uint32_t s = isqrt32(Ap);
    uint32_t r = (1u << 30) / (s ? s : 1u);        /* s is never 0; the guard stops gcc emitting ebreak */
    int32_t ym, ye;
    quantize(q, tmp, n, 0, &ym, &ye);
    *qm = (int32_t)(((uint64_t)(uint32_t)ym * r + (1u << 15)) >> 16);
    *qe = ye + 14 + gf + j + t / 2;
}

/* The hot loop (~99% of multiply-adds). Four sums because the core has no forwarding. */
static int32_t dot_i8(const int8_t *a, const int8_t *b, int n) {
    int32_t s0 = 0, s1 = 0, s2 = 0, s3 = 0;
    int j = 0;
    for (; j + 8 <= n; j += 8) {
        s0 += a[j] * b[j];
        s1 += a[j + 1] * b[j + 1];
        s2 += a[j + 2] * b[j + 2];
        s3 += a[j + 3] * b[j + 3];
        s0 += a[j + 4] * b[j + 4];
        s1 += a[j + 5] * b[j + 5];
        s2 += a[j + 6] * b[j + 6];
        s3 += a[j + 7] * b[j + 7];
    }
    for (; j < n; j++) s0 += a[j] * b[j];
    return (s0 + s1) + (s2 + s3);
}

/* out (Q16) = W @ x, int8 rows with per-row scales */
static void matmul(int32_t *out, const int8_t *xq, int32_t xm, int32_t xe,
                   const int8_t *w, const int32_t *wm, const int32_t *we, int n, int d) {
    for (int i = 0; i < d; i++) {
        int32_t acc = dot_i8(w + i * n, xq, n);
        out[i] = requant((int64_t)acc * (wm[i] * xm), we[i] + xe - 16);
    }
}

/* ------------------------------------------------------------------ transformer pieces */
static void rope(int32_t *v, int n, int pos) {
    const int32_t *cs = I32(OFF_ROPE_COS) + pos * (HEAD_SIZE / 2);
    const int32_t *sn = I32(OFF_ROPE_SIN) + pos * (HEAD_SIZE / 2);
    for (int i = 0, f = 0; i < n; i += 2) {
        int64_t v0 = v[i], v1 = v[i + 1];
        v[i]     = clampq(requant(v0 * cs[f] - v1 * sn[f], 30), QKV_CLAMP);
        v[i + 1] = clampq(requant(v0 * sn[f] + v1 * cs[f], 30), QKV_CLAMP);
        if (++f == HEAD_SIZE / 2) f = 0;
    }
}

static int32_t swiglu(int32_t a, int32_t b) {    /* silu(a) * b, Q16 */
    uint32_t e = (uint32_t)exp_q30(a >= 0 ? -a : a);
    uint32_t d15 = ((1u << 30) + e) >> 15;
    int32_t sig = (int32_t)((a >= 0 ? (1u << 30) : e) / d15);
    int64_t s = ((int64_t)a * sig + (1 << 14)) >> 15;
    return requant(s * b, 16);
}

static void attention(int32_t *out, const int32_t *q, const int32_t *kc, const int32_t *vc, int pos) {
    for (int h = 0; h < N_HEADS; h++) {
        const int32_t *qh = q + h * HEAD_SIZE;
        int koff = (h / KV_MUL) * HEAD_SIZE;
        int32_t mx = INT32_MIN;
        for (int t = 0; t <= pos; t++) {           /* 1/sqrt(head_size) is folded into wq */
            const int32_t *k = kc + t * KV_DIM + koff;
            int64_t d = 0;
            for (int i = 0; i < HEAD_SIZE; i++) d += (int64_t)qh[i] * k[i];
            att[t] = requant(d, 16);
            if (att[t] > mx) mx = att[t];
        }
        uint64_t sum = 0;                          /* softmax */
        for (int t = 0; t <= pos; t++) {
            int64_t dd = (int64_t)att[t] - mx;
            att[t] = dd <= -EXP_CUTOFF_Q16 ? 0 : exp_q30((int32_t)dd);
            sum += (uint32_t)att[t];
        }
        int b = bitlen64(sum);                     /* sum >= 2^30; the guards stop gcc emitting ebreak */
        if (b < 16) b = 16;
        uint32_t d = (uint32_t)(sum >> (b - 16));
        uint32_t inv = (1u << 30) / (d ? d : 1u);
        for (int t = 0; t <= pos; t++)
            att[t] = (int32_t)(((int64_t)att[t] * inv + ((int64_t)1 << (b - 3))) >> (b - 2));
#if VISUALIZE
        if (viz_att_on)
            for (int c = 0; c < VIZ_HIST; c++) {
                int t = pos - (VIZ_HIST - 1) + c;
                viz_att[h][c] = t >= 0 ? att[t] : -1;
            }
#endif
        int64_t acc[HEAD_SIZE];
        for (int i = 0; i < HEAD_SIZE; i++) acc[i] = 0;
        for (int t = 0; t <= pos; t++) {
            const int32_t *v = vc + t * KV_DIM + koff;
            for (int i = 0; i < HEAD_SIZE; i++) acc[i] += (int64_t)att[t] * v[i];
        }
        for (int i = 0; i < HEAD_SIZE; i++) out[h * HEAD_SIZE + i] = requant(acc[i], 16);
    }
}

static const int32_t *forward(int token, int pos) {
    int32_t xm, xe;
    {   /* token embedding -> residual stream */
        const int8_t *row = I8(OFF_TOK_EMB) + token * DIM;
        int32_t m = I32(OFF_TOK_EMB_M)[token];
        int sh = I32(OFF_TOK_EMB_E)[token] - 16;
        for (int i = 0; i < DIM; i++) x[i] = requant((int64_t)row[i] * m, sh);
    }
    VIZ_KEEP_X(0);
    for (int l = 0; l < N_LAYERS; l++) {
        int32_t *kc = key_cache + l * STEPS * KV_DIM;
        int32_t *vc = value_cache + l * STEPS * KV_DIM;
        int32_t *k = kc + pos * KV_DIM, *v = vc + pos * KV_DIM;

        rmsnorm_quant(act, &xm, &xe, x, I32(OFF_RMS_ATT) + l * DIM, I32(OFF_RMS_ATT_F)[l], DIM);
        matmul(qv, act, xm, xe, I8(OFF_WQ) + l * DIM * DIM,
               I32(OFF_WQ_M) + l * DIM, I32(OFF_WQ_E) + l * DIM, DIM, DIM);
        matmul(k, act, xm, xe, I8(OFF_WK) + l * KV_DIM * DIM,
               I32(OFF_WK_M) + l * KV_DIM, I32(OFF_WK_E) + l * KV_DIM, DIM, KV_DIM);
        matmul(v, act, xm, xe, I8(OFF_WV) + l * KV_DIM * DIM,
               I32(OFF_WV_M) + l * KV_DIM, I32(OFF_WV_E) + l * KV_DIM, DIM, KV_DIM);
        rope(qv, DIM, pos);
        rope(k, KV_DIM, pos);
        for (int i = 0; i < KV_DIM; i++) v[i] = clampq(v[i], QKV_CLAMP);
        VIZ_ATT_SELECT(l);
        attention(xb, qv, kc, vc, pos);
        quantize(act, xb, DIM, 16, &xm, &xe);
        matmul(xb2, act, xm, xe, I8(OFF_WO) + l * DIM * DIM,
               I32(OFF_WO_M) + l * DIM, I32(OFF_WO_E) + l * DIM, DIM, DIM);
        for (int i = 0; i < DIM; i++) x[i] = sat32((int64_t)x[i] + xb2[i]);

        rmsnorm_quant(act, &xm, &xe, x, I32(OFF_RMS_FFN) + l * DIM, I32(OFF_RMS_FFN_F)[l], DIM);
        matmul(hb, act, xm, xe, I8(OFF_W1) + l * HIDDEN_DIM * DIM,
               I32(OFF_W1_M) + l * HIDDEN_DIM, I32(OFF_W1_E) + l * HIDDEN_DIM, DIM, HIDDEN_DIM);
        matmul(hb2, act, xm, xe, I8(OFF_W3) + l * HIDDEN_DIM * DIM,
               I32(OFF_W3_M) + l * HIDDEN_DIM, I32(OFF_W3_E) + l * HIDDEN_DIM, DIM, HIDDEN_DIM);
        for (int i = 0; i < HIDDEN_DIM; i++) hb[i] = swiglu(hb[i], hb2[i]);
        quantize(act, hb, HIDDEN_DIM, 16, &xm, &xe);
        matmul(xb, act, xm, xe, I8(OFF_W2) + l * DIM * HIDDEN_DIM,
               I32(OFF_W2_M) + l * DIM, I32(OFF_W2_E) + l * DIM, HIDDEN_DIM, DIM);
        for (int i = 0; i < DIM; i++) x[i] = sat32((int64_t)x[i] + xb[i]);
        VIZ_KEEP_X(l + 1);
    }
    rmsnorm_quant(act, &xm, &xe, x, I32(OFF_RMS_FINAL), I32(OFF_RMS_FINAL_F)[0], DIM);
    matmul(logits, act, xm, xe, I8(OFF_CLS), I32(OFF_CLS_M), I32(OFF_CLS_E), DIM, VOCAB_SIZE);
    return logits;
}

/* ------------------------------------------------------------------ sampling */
static uint32_t mix32(uint32_t h) {               /* scrambles the seed so small seeds work */
    h ^= h >> 16;
    h *= 0x85EBCA6Bu;
    h ^= h >> 13;
    h *= 0xC2B2AE35u;
    h ^= h >> 16;
    return h ? h : 1u;
}
static uint32_t rand_u32(void) {                  /* xorshift32 */
    uint32_t r = rng_state;
    r ^= r << 13;
    r ^= r >> 17;
    r ^= r << 5;
    return rng_state = r;
}

static int argmax(const int32_t *v, int n) {
    int best = 0;
    for (int i = 1; i < n; i++) if (v[i] > v[best]) best = i;
    return best;
}

static int sample(int32_t *lg, int n) {           /* overwrites lg */
#if TEMP_PERCENT == 0
    return argmax(lg, n);
#else
    int32_t mx = lg[argmax(lg, n)];
    uint32_t total = 0;
    for (int i = 0; i < n; i++) {
        int64_t z = (((int64_t)lg[i] - mx) * ((65536 * 100) / TEMP_PERCENT) + (1 << 15)) >> 16;
        lg[i] = z <= -EXP_CUTOFF_Q16 ? 0 : exp_q30((int32_t)z) >> 14;
        total += (uint32_t)lg[i];
    }
    uint32_t r = (uint32_t)(((uint64_t)rand_u32() * total) >> 32);
    uint32_t cum = 0;
    for (int i = 0; i < n; i++) {
        cum += (uint32_t)lg[i];
        if (r < cum) return i;
    }
    return n - 1;
#endif
}

static uint32_t hash_logits(const int32_t *l, int n) { /* FNV-1a, same as export_model.py */
    uint32_t h = 2166136261u;
    for (int i = 0; i < n; i++) { h ^= (uint32_t)l[i]; h *= 16777619u; }
    return h;
}

/* ------------------------------------------------------------------ screen */
#define COLOR_BG    0x00101820u
#define COLOR_TEXT  0x00E8E8E8u
#define COLOR_TITLE 0x00FFC040u
#define COLOR_STATS 0x0060D0FFu
#define COLOR_DIM   0x00809098u
#define COLOR_LINE  0x00304858u
#define COLOR_BAR   0x003890C0u
#if USE_FRAMEBUFFER
#define FB_W 320
#define FB_H 240
#define CON_COLS (FB_W / 8)
static const uint8_t font8x8[95][8];               /* at the bottom of the file */

#if VISUALIZE
/* top to bottom: title, story, layer activity, attention, next-word candidates */
#define VIZ_W      256
#define VIZ_X0     (FB_W - VIZ_W)
#define ACT_ROWS   (N_LAYERS + 1)
#define ACT_ROW_H  (ACT_ROWS <= 7 ? 8 : ACT_ROWS <= 14 ? 4 : 2)
#define ACT_COLS   (DIM < 64 ? DIM : 64)
#define ACT_CELL_W (VIZ_W / ACT_COLS)
#define ATT_ROW_H  (N_HEADS <= 24 ? 24 / N_HEADS : 1)
#define ATT_CELL_W (VIZ_W / VIZ_HIST)
#define CAND_N     5
#define BAR_W      (VIZ_W - 40)
#define DIV_H      2
#define ACT_H      (ACT_ROWS * ACT_ROW_H)
#define ATT_H      (N_HEADS * ATT_ROW_H)
#define PANEL_H    (ACT_H + ATT_H + CAND_N * 8 + 3 * DIV_H)
#define TEXT_Y0    8
#define TEXT_ROWS  ((FB_H - TEXT_Y0 - PANEL_H) / 8)
#define ACT_Y0     (TEXT_Y0 + TEXT_ROWS * 8 + DIV_H)
#define ATT_Y0     (ACT_Y0 + ACT_H + DIV_H)
#define CAND_Y0    (ATT_Y0 + ATT_H + DIV_H)
#if TEXT_ROWS < 4
#error "this model has too many layers/heads for the on-screen panels; build with -DVISUALIZE=0"
#endif
#else
#define TEXT_Y0    0
#define TEXT_ROWS  (FB_H / 8)
#endif

static void draw_glyph(int px, int py, unsigned char ch, uint32_t fg) {
    const uint8_t *g = font8x8[(ch >= 32 && ch < 127) ? ch - 32 : 0];
    volatile unsigned int *p = FRAMEBUFFER + py * FB_W + px;
    for (int y = 0; y < 8; y++, p += FB_W)
        for (int xx = 0; xx < 8; xx++) p[xx] = ((g[y] >> xx) & 1) ? fg : COLOR_BG;
}
#if VISUALIZE
static void draw_str(int px, int py, const char *s, int width, uint32_t fg) {   /* pads with spaces */
    for (int k = 0; k < width; k++, px += 8) {
        draw_glyph(px, py, (unsigned char)(*s ? *s : ' '), fg);
        if (*s) s++;
    }
}
static void fill_rect(int px, int py, int w, int h, uint32_t c) {
    volatile unsigned int *p = FRAMEBUFFER + py * FB_W + px;
    for (int y = 0; y < h; y++, p += FB_W)
        for (int xx = 0; xx < w; xx++) p[xx] = c;
}

#endif

/* scrolling story text; keeps its own copy because the framebuffer is write-only */
static char con_text[TEXT_ROWS][CON_COLS];
static uint32_t con_color[TEXT_ROWS][CON_COLS];
static int con_row, con_col, word_len;
static uint32_t cur_color;
static char word[CON_COLS];

static void con_draw(int row, int col) {
    draw_glyph(col * 8, TEXT_Y0 + row * 8, (unsigned char)con_text[row][col], con_color[row][col]);
}
static void con_redraw(void) {
    for (int r = 0; r < TEXT_ROWS; r++)
        for (int c = 0; c < CON_COLS; c++) con_draw(r, c);
}
static void con_clear(void) {
    for (int r = 0; r < TEXT_ROWS; r++)
        for (int c = 0; c < CON_COLS; c++) { con_text[r][c] = ' '; con_color[r][c] = COLOR_TEXT; }
    con_row = con_col = word_len = 0;
    cur_color = COLOR_TEXT;
    con_redraw();
}
static void con_newline(void) {
    con_col = 0;
    if (++con_row < TEXT_ROWS) return;
    for (int r = 1; r < TEXT_ROWS; r++)
        for (int c = 0; c < CON_COLS; c++) {
            con_text[r - 1][c] = con_text[r][c];
            con_color[r - 1][c] = con_color[r][c];
        }
    for (int c = 0; c < CON_COLS; c++) con_text[TEXT_ROWS - 1][c] = ' ';
    con_row = TEXT_ROWS - 1;
    con_redraw();
}
static void con_put_raw(char ch) {
    if (con_col == CON_COLS) con_newline();
    con_text[con_row][con_col] = ch;
    con_color[con_row][con_col] = cur_color;
    con_draw(con_row, con_col++);
}
static void con_flush_word(void) {                /* word wrap */
    if (word_len > CON_COLS - con_col && con_col > 0) con_newline();
    for (int i = 0; i < word_len; i++) con_put_raw(word[i]);
    word_len = 0;
}
static void con_putc(unsigned char ch) {
    if (ch == '\n') { con_flush_word(); con_newline(); return; }
    if (ch == ' ') {
        con_flush_word();
        if (con_col > 0 && con_col < CON_COLS) con_put_raw(' ');
        return;
    }
    if (ch < 32 || ch >= 127) return;              /* font is ASCII only */
    if (word_len == CON_COLS) con_flush_word();
    word[word_len++] = (char)ch;
}
#else
static void con_putc(unsigned char ch) { (void)ch; }
#endif

#if VISUALIZE
/* ------------------------------------------------------------------ live view of the model */
static int viz_top[CAND_N];                        /* likeliest next tokens */
static uint32_t viz_w[VOCAB_SIZE], viz_total;
static uint8_t sqrt_lut[256];

static uint32_t rgb4(int r, int g, int b) {        /* 4 bits per channel, like the VGA */
    return (uint32_t)(r * 17) << 16 | (uint32_t)(g * 17) << 8 | (uint32_t)(b * 17);
}
static uint32_t uabs32(int32_t v) { return v < 0 ? 0u - (uint32_t)v : (uint32_t)v; }
static uint32_t heat(int lv) {                     /* 0..15: black - purple - red - orange - yellow */
    int r = 2 * lv > 15 ? 15 : 2 * lv, g = 2 * lv - 15 > 0 ? 2 * lv - 15 : 0;
    int b = lv < 6 ? lv : (12 - lv > 0 ? 12 - lv : 0);
    return rgb4(r, g, b);
}

/* next-token odds, computed exactly as sample() does */
static void viz_probs(const int32_t *lg) {
    int32_t mx = lg[0];
    for (int i = 1; i < VOCAB_SIZE; i++) if (lg[i] > mx) mx = lg[i];
    uint32_t total = 0;
    for (int k = 0; k < CAND_N; k++) viz_top[k] = -1;
    for (int i = 0; i < VOCAB_SIZE; i++) {
        int64_t z = (((int64_t)lg[i] - mx) * ((65536 * 100) / (TEMP_PERCENT ? TEMP_PERCENT : 100)) + (1 << 15)) >> 16;
        uint32_t w = z <= -EXP_CUTOFF_Q16 ? 0 : (uint32_t)exp_q30((int32_t)z) >> 14;
        viz_w[i] = w;
        total += w;
        if (viz_top[CAND_N - 1] < 0 || w > viz_w[viz_top[CAND_N - 1]]) {
            int k = CAND_N - 1;
            while (k > 0 && (viz_top[k - 1] < 0 || w > viz_w[viz_top[k - 1]])) { viz_top[k] = viz_top[k - 1]; k--; }
            viz_top[k] = i;
        }
    }
    viz_total = total ? total : 1;
}

static int token_label(int tok, char *out, int max) {
    static const char end[] = "(end)";
    int n = 0;
    if (tok == 1) { for (; end[n] && n < max; n++) out[n] = end[n]; return n; }
    const uint32_t *off = U32(OFF_VOCAB_OFF);
    const uint8_t *bytes = (const uint8_t *)(model_blob + OFF_VOCAB_BYTES);
    uint32_t a = off[tok], b = off[tok + 1];
    if (b == a + 1 && bytes[a] == ' ') {           /* the lone-space token */
        static const char sp[] = "(space)";
        for (; sp[n] && n < max; n++) out[n] = sp[n];
        return n;
    }
    if (a < b && bytes[a] == ' ') a++;
    for (; a < b && n < max; a++) {
        unsigned char ch = bytes[a];
        if (ch == '\n') { if (n + 2 > max) break; out[n++] = '\\'; out[n++] = 'n'; }
        else out[n++] = (char)(ch >= 32 && ch < 127 ? ch : '?');
    }
    return n;
}

static void viz_frame(void) {                      /* title, labels, dividers */
    for (int i = 0; i < 256; i++) sqrt_lut[i] = (uint8_t)isqrt32((uint32_t)i);
    fill_rect(0, 0, FB_W, FB_H, COLOR_BG);
    draw_str(0, 0, TITLE, CON_COLS, COLOR_TITLE);
    fill_rect(0, ACT_Y0 - DIV_H, FB_W, 1, COLOR_LINE);
    fill_rect(0, ATT_Y0 - DIV_H, FB_W, 1, COLOR_LINE);
    fill_rect(0, CAND_Y0 - DIV_H, FB_W, 1, COLOR_LINE);
    if (ACT_ROW_H == 8) {
        draw_str(0, ACT_Y0, "embed", 8, COLOR_DIM);
        for (int l = 1; l < ACT_ROWS; l++) {
            char s[9] = "layer   ";
            if (l >= 10) { s[6] = (char)('0' + l / 10); s[7] = (char)('0' + l % 10); }
            else s[6] = (char)('0' + l);
            draw_str(0, ACT_Y0 + l * 8, s, 8, COLOR_DIM);
        }
    } else {
        draw_str(0, ACT_Y0, "layers", 8, COLOR_DIM);
    }
    draw_str(0, ATT_Y0, "attend", 8, COLOR_DIM);
    if (ATT_H >= 16) draw_str(0, ATT_Y0 + 8, STR(N_HEADS) " heads", 8, COLOR_DIM);
}


static void viz_draw(int chosen) {                 /* redrawn for every token */
    static int32_t row[DIM];
    for (int r = 0; r < ACT_ROWS; r++) {           /* row 0: embedding; row l: what layer l added */
        uint32_t mx = 1;
        for (int i = 0; i < DIM; i++) {
            row[i] = r == 0 ? viz_x[0][i] : sat32((int64_t)viz_x[r][i] - viz_x[r - 1][i]);
            uint32_t a = uabs32(row[i]);
            if (a > mx) mx = a;
        }
        int s = bitlen32(mx) > 23 ? bitlen32(mx) - 23 : 0;
        uint32_t m = mx >> s;
        for (int c = 0; c < ACT_COLS; c++) {
            int i0 = c * DIM / ACT_COLS, i1 = (c + 1) * DIM / ACT_COLS;
            int32_t v = row[i0];
            for (int i = i0 + 1; i < i1; i++) if (uabs32(row[i]) > uabs32(v)) v = row[i];
            int lv = sqrt_lut[(uabs32(v) >> s) * 255u / (m ? m : 1u)];
            uint32_t col = v >= 0 ? rgb4(lv, lv * 2 / 3, lv / 4) : rgb4(lv / 4, lv * 2 / 3, lv);
            fill_rect(VIZ_X0 + c * ACT_CELL_W, ACT_Y0 + r * ACT_ROW_H, ACT_CELL_W, ACT_ROW_H - 1, col);
        }
    }
    /* attention: one row per head, newest token on the right */
    for (int h = 0; h < N_HEADS; h++)
        for (int c = 0; c < VIZ_HIST; c++) {
            int32_t a = viz_att[h][c];
            uint32_t col = COLOR_BG;
            if (a >= 0) {
                uint32_t q = (uint32_t)a >> 8;
                col = heat(sqrt_lut[q > 255 ? 255 : q]);
            }
            fill_rect(VIZ_X0 + c * ATT_CELL_W, ATT_Y0 + h * ATT_ROW_H, ATT_CELL_W - 1, ATT_ROW_H, col);
        }
    /* next word: top guesses; the pick is amber */
    int show[CAND_N], found = 0;
    for (int k = 0; k < CAND_N; k++) { show[k] = viz_top[k]; if (show[k] == chosen) found = 1; }
    if (!found) show[CAND_N - 1] = chosen;          /* a long shot was picked: show it anyway */
    for (int k = 0; k < CAND_N; k++) {
        int y = CAND_Y0 + k * 8, tok = show[k];
        char label[9], pct[5];
        int n = tok >= 0 ? token_label(tok, label, 8) : 0;
        label[n] = 0;
        uint32_t w = tok >= 0 ? viz_w[tok] : 0;
        uint32_t fg = tok == chosen ? COLOR_TITLE : COLOR_TEXT;
        draw_str(0, y, label, 8, fg);
        int bar = (int)(w * (uint32_t)BAR_W / viz_total);
        fill_rect(VIZ_X0, y + 1, bar, 6, tok == chosen ? COLOR_TITLE : COLOR_BAR);
        fill_rect(VIZ_X0 + bar, y + 1, BAR_W - bar, 6, COLOR_BG);
        uint32_t p = w * 100u / viz_total;
        int j = 0;
        if (p >= 100) pct[j++] = '1';
        if (p >= 10) pct[j++] = (char)('0' + (p / 10) % 10);
        pct[j++] = (char)('0' + p % 10);
        pct[j++] = '%';
        pct[j] = 0;
        draw_str(VIZ_X0 + BAR_W + 4, y, pct, 4, COLOR_DIM);
    }
}
#endif

static void con_color_set(uint32_t c) {
#if USE_FRAMEBUFFER
    con_flush_word();
    cur_color = c;
#else
    (void)c;
#endif
}

static void say(char *s) {                        /* to UART and screen */
    for (; *s; s++) { uart_putc(*s); con_putc((unsigned char)*s); }
}
static void say_dec(unsigned int v) {
    char buf[11];
    int n = 10;
    buf[n] = 0;
    do { buf[--n] = (char)('0' + v % 10); v /= 10; } while (v);
    say(buf + n);
}

/* ------------------------------------------------------------------ top level */
static void emit_token(int prev, int tok) {
    const uint32_t *off = U32(OFF_VOCAB_OFF);
    const uint8_t *bytes = (const uint8_t *)(model_blob + OFF_VOCAB_BYTES);
    uint32_t a = off[tok], b = off[tok + 1];
    if (prev == 1 && a < b && bytes[a] == ' ') a++;    /* no leading space after BOS */
    for (; a < b; a++) { uart_putc((char)bytes[a]); con_putc(bytes[a]); }
}

static int check_blob(void) {
    const uint32_t *h = U32(OFF_HEADER);
    if (h[0] == BLOB_MAGIC && h[1] == DIM && h[2] == HIDDEN_DIM && h[3] == N_LAYERS &&
        h[4] == N_HEADS && h[5] == N_KV_HEADS && h[6] == VOCAB_SIZE && h[7] == SEQ_LEN)
        return 1;
    debug_log("ERROR: model data in memory is corrupt (header mismatch) -- was the whole image loaded?\n");
    return 0;
}

static int selftest(void) {                       /* greedy decode vs. golden logit hashes */
    int token = PROMPT_TOKENS[0];
    if (SELFTEST_STEPS == 0) { debug_log("selftest: skipped\n"); return 1; }
    debug_log("selftest: ");
    for (int pos = 0; pos < SELFTEST_STEPS; pos++) {
        const int32_t *lg = forward(token, pos);
        uint32_t h = hash_logits(lg, VOCAB_SIZE);
        int next = pos < N_PROMPT - 1 ? PROMPT_TOKENS[pos + 1] : argmax(lg, VOCAB_SIZE);
        if (h != GOLDEN_HASH[pos] || next != GOLDEN_TOKENS[pos]) {
            debug_log("FAIL at pos ");
            debug_dec((unsigned int)pos);
            trace("\n  logits hash ", h);
            trace("  expected    ", GOLDEN_HASH[pos]);
            trace("  token       ", (unsigned int)next);
            trace("  expected    ", (unsigned int)GOLDEN_TOKENS[pos]);
            return 0;
        }
        uart_putc('.');
        token = next;
    }
    debug_log(" PASS (bit-exact with export_model.py)\n");
    return 1;
}

static void tell_story(int story) {
    int token = PROMPT_TOKENS[0], pos = 0, n = 0;
    con_color_set(COLOR_TITLE);
    say("-- story ");
    say_dec((unsigned int)story + 1);
    say(" --\n");
    con_color_set(COLOR_TEXT);
    unsigned int t0 = read_timer();
    while (pos < STEPS) {
        int32_t *lg = (int32_t *)forward(token, pos);
#if VISUALIZE
        viz_probs(lg);                             /* before sample() overwrites lg */
#endif
        int next = pos < N_PROMPT - 1 ? PROMPT_TOKENS[pos + 1] : sample(lg, VOCAB_SIZE);
#if VISUALIZE
        viz_draw(next);
#endif
        pos++;
        if (next == 1) break;                      /* BOS = end of story */
        emit_token(token, next);
        token = next;
        n++;
    }
    unsigned int dt = read_timer() - t0;
    con_color_set(COLOR_STATS);
    say("\n[");
    say_dec((unsigned int)n);
    say(" tokens in ");
    say_dec(dt / 1000);
    say(" ms, ");
    say_dec(n ? dt / (unsigned int)n / 1000 : 0);
    say(" ms/token]\n\n");
}

int main(void) {
    debug_log("\nboot: integer-only llama2, model " MODEL_NAME "\n");
    if (!check_blob()) for (;;) {}
#if VISUALIZE
    viz_frame();
#endif
#if USE_FRAMEBUFFER
    con_clear();
#endif
    int ok = selftest();
    uint32_t seed = SEED ? SEED : (read_timer() * 2654435761u) ^ 0x2545F491u;
    con_color_set(COLOR_TITLE);
#if VISUALIZE
    debug_log(TITLE "\n");
#else
    say(TITLE "\n");
#endif
    if (!ok) say("(selftest FAILED -- see UART)\n");
    say("\n");
    for (int story = 0; MAX_STORIES == 0 || story < MAX_STORIES; story++) {
        rng_state = mix32(seed);
        trace("seed=", seed);                      /* replay: export_model.py ... --sample 0x<seed> 80 */
        tell_story(story);
        seed = rand_u32();
    }
#ifdef HOST_TEST
    FILE *img = fopen("screen.ppm", "wb");
    if (img) {
        fprintf(img, "P6 320 240 255\n");
        for (int i = 0; i < 320 * 240; i++) {
            unsigned int p = host_fb[i];
            fputc((p >> 16) & 255, img); fputc((p >> 8) & 255, img); fputc(p & 255, img);
        }
        fclose(img);
    }
#endif
    return 0;
}

#if USE_FRAMEBUFFER
/* font8x8_basic by Daniel Hepper, public domain (ASCII 32..126; bit 0 = leftmost pixel) */
static const uint8_t font8x8[95][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},
    {0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00},
    {0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00},
    {0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00},
    {0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00},
    {0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00},
    {0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00},
    {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},
    {0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06},
    {0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00},
    {0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00},
    {0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},
    {0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00},
    {0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00},
    {0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00},
    {0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00},
    {0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00},
    {0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00},
    {0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00},
    {0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},
    {0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00},
    {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00},
    {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06},
    {0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00},
    {0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00},
    {0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00},
    {0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00},
    {0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00},
    {0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},
    {0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00},
    {0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00},
    {0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00},
    {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00},
    {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00},
    {0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00},
    {0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00},
    {0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},
    {0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00},
    {0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00},
    {0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00},
    {0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00},
    {0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00},
    {0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},
    {0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00},
    {0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00},
    {0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00},
    {0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00},
    {0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00},
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},
    {0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00},
    {0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00},
    {0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00},
    {0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00},
    {0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00},
    {0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00},
    {0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00},
    {0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},
    {0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00},
    {0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00},
    {0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00},
    {0x38, 0x30, 0x30, 0x3E, 0x33, 0x33, 0x6E, 0x00},
    {0x00, 0x00, 0x1E, 0x33, 0x3F, 0x03, 0x1E, 0x00},
    {0x1C, 0x36, 0x06, 0x0F, 0x06, 0x06, 0x0F, 0x00},
    {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F},
    {0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00},
    {0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},
    {0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E},
    {0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00},
    {0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},
    {0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00},
    {0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00},
    {0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00},
    {0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F},
    {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78},
    {0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00},
    {0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00},
    {0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00},
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00},
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},
    {0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00},
    {0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00},
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F},
    {0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00},
    {0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00},
    {0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},
    {0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00},
    {0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};
#endif
