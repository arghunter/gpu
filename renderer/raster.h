#ifndef RASTER_H
#define RASTER_H

#include "geom.h"
#include "gpu.h"

/* Full-screen depth buffer in DRAM. M3 replaces this with per-tile depth
 * held in registers, which is where the real win is -- a read-modify-write
 * per pixel costs two lane transactions each on this LSU. Keeping it simple
 * here means M2's vectorised output can be diffed against a baseline whose
 * correctness is not in question. */
extern zfx raster_zbuf[SCREEN_W * SCREEN_H];

/* Rendering targets this rather than the display. The VGA scans the display
 * out continuously, so drawing straight into it shows partially-built frames
 * -- the renderer takes ~25 ms and the beam passes every 16.7 ms. Compositing
 * into DRAM and blitting afterwards shrinks the tear window from the whole
 * render to the length of the copy. */
extern unsigned int raster_fb[SCREEN_W * SCREEN_H];

/* Blit the back buffer to the display. Warp-partitioned by row exactly like
 * the renderer, so each warp copies the rows it just drew and no barrier is
 * needed in between. */
void raster_present(void);

unsigned int raster_zsum(void);
/* Warps own interleaved rows: warp w draws rows w, w+NWARPS_R, ... Both the
 * clear and the rasteriser use the same split, so warps never touch each
 * other's pixels and the shared depth buffer needs no synchronisation --
 * which matters, because this hardware has no atomics. */
#ifndef NWARPS_R
#  ifdef GPU_HOST
#    define NWARPS_R 1  /* the host reference is one warp and owns every row */
#  else
#    define NWARPS_R 4
#  endif
#endif

void raster_clear(unsigned int color);
void raster_tri(const svert_t* a, const svert_t* b, const svert_t* c);

#endif /* RASTER_H */
