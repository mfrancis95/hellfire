#include <stdlib.h>
#include "software_renderer.h"

void renderPixels(unsigned *indices, unsigned *pixels, unsigned width, unsigned height) {
    for (unsigned x = 0; x < width; x++) {
        for (unsigned y = 1; y < height; y++) {
            unsigned src = x + y * width;
            unsigned index = indices[src];
            if (index) {
                unsigned random = rand() % 3 & 3;
                unsigned dst = src - random + 1;
                indices[dst - width] = index - (random & 1);
                pixels[dst - width] = palette[index - (random & 1)];
            }
            else {
                indices[src - width] = 0;
                pixels[src - width] = palette[0];
            }
        }
    }
}