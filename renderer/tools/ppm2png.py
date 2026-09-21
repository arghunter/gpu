#!/usr/bin/env python3
"""ppm2png in.ppm out.png -- so the host reference can be viewed directly."""
import sys, zlib, struct

def read_ppm(path):
    d = open(path, 'rb').read()
    tok, i = [], 2
    while len(tok) < 3:
        while d[i:i+1].isspace(): i += 1
        j = i
        while not d[j:j+1].isspace(): j += 1
        tok.append(int(d[i:j])); i = j
    i += 1
    w, h, _ = tok
    return w, h, d[i:i+w*h*3]

def chunk(t, d):
    return struct.pack('>I', len(d)) + t + d + struct.pack('>I', zlib.crc32(t + d) & 0xffffffff)

w, h, px = read_ppm(sys.argv[1])
raw = b''.join(b'\x00' + px[y*w*3:(y+1)*w*3] for y in range(h))
open(sys.argv[2], 'wb').write(
    b'\x89PNG\r\n\x1a\n'
    + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 2, 0, 0, 0))
    + chunk(b'IDAT', zlib.compress(raw, 9))
    + chunk(b'IEND', b''))
print(f"{sys.argv[2]}: {w}x{h}")
