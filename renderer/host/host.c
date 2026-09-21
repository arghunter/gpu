/* Host reference: renders with the same sources at NLANES == 1 and writes a
 * PPM, so the simulated image can be diffed against a ground truth that runs
 * in milliseconds. */
#include <stdio.h>
#include <stdlib.h>
#include "../gpu.h"
#include "../raster.h"

unsigned int host_fb[SCREEN_W * SCREEN_H];

void render_frame(int frame);

int main(int argc, char** argv) {
    int frame = (argc > 1) ? atoi(argv[1]) : 0;
    const char* out = (argc > 2) ? argv[2] : "ref.ppm";

    render_frame(frame);
    raster_present();

    FILE* f = fopen(out, "wb");
    if (!f) { perror(out); return 1; }
    fprintf(f, "P6\n%d %d\n255\n", SCREEN_W, SCREEN_H);
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
        unsigned int c = host_fb[i];
        /* The VGA path keeps only the top nibble of each channel, so the
         * reference must quantise the same way or every pixel differs. */
        unsigned char rgb[3] = {
            (unsigned char)(((c >> 16) & 0xF0) | (((c >> 16) & 0xF0) >> 4)),
            (unsigned char)(((c >>  8) & 0xF0) | (((c >>  8) & 0xF0) >> 4)),
            (unsigned char)(((c      ) & 0xF0) | (((c      ) & 0xF0) >> 4)),
        };
        fwrite(rgb, 1, 3, f);
    }
    fclose(f);
    fprintf(stderr, "wrote %s\n", out);
    fprintf(stderr, "zsum  %08X\n", raster_zsum());
    return 0;
}
