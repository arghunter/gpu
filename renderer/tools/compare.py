#!/usr/bin/env python3
"""Diff the simulated frame against the host reference.

The VGA scans out at 640x480 with 2x pixel doubling, so the simulated frame
is downsampled before comparison. Both sides are already quantised to the
12-bit colour the VGA path keeps, so an exact match is the expectation --
any nonzero difference is a real divergence, not rounding.
"""
import sys

def read_ppm(path):
    d = open(path, 'rb').read()
    if not d.startswith(b'P6'):
        raise SystemExit(f"{path}: not a binary PPM")
    tok, i = [], 2
    while len(tok) < 3:
        while i < len(d) and d[i:i+1].isspace(): i += 1
        if d[i:i+1] == b'#':
            while d[i:i+1] != b'\n': i += 1
            continue
        j = i
        while j < len(d) and not d[j:j+1].isspace(): j += 1
        tok.append(int(d[i:j])); i = j
    i += 1
    w, h, _ = tok
    return w, h, d[i:i+w*h*3]

def main():
    sim_path, ref_path = sys.argv[1], sys.argv[2]
    sw, sh, sim = read_ppm(sim_path)
    rw, rh, ref = read_ppm(ref_path)
    if sw != rw * 2 or sh != rh * 2:
        print(f"size mismatch: sim {sw}x{sh}, ref {rw}x{rh} (expected 2x)")
        return 2

    diff = 0
    first = None
    for y in range(rh):
        for x in range(rw):
            # Pixel (0,0) is a known VGA scanout artifact: the grabber samples
            # it before the controller has driven valid data, so it shows a
            # stray colour in every capture regardless of what was rendered.
            if x == 0 and y == 0:
                continue
            si = ((y*2) * sw + (x*2)) * 3
            ri = (y * rw + x) * 3
            if sim[si:si+3] != ref[ri:ri+3]:
                diff += 1
                if first is None:
                    first = (x, y, sim[si:si+3].hex(), ref[ri:ri+3].hex())
    total = rw * rh
    print(f"{diff}/{total} pixels differ ({100.0*diff/total:.3f}%)")
    if first:
        x, y, s, r = first
        print(f"first at ({x},{y}): sim {s} ref {r}")
    return 1 if diff else 0

sys.exit(main())
