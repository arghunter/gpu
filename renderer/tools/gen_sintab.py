#!/usr/bin/env python3
"""Emit renderer/sintab.c: one full turn of sine in Q16.16.

Committed rather than computed at boot so there is no init ordering to get
wrong and no startup cost. Re-run after changing SINTAB_BITS in fx.h.
"""
import math, sys

BITS = 10
N = 1 << BITS
vals = []
for i in range(N):
    s = math.sin(2.0 * math.pi * i / N)
    q = int(round(s * 65536.0))
    q = max(-2147483648, min(2147483647, q))
    vals.append(q)

out = ['#include "fx.h"', '', f'const fx fx_sintab[{N}] = {{']
for i in range(0, N, 8):
    out.append('    ' + ' '.join(f'{v},'.rjust(8) for v in vals[i:i+8]))
out += ['};', '']
sys.stdout.write('\n'.join(out))
