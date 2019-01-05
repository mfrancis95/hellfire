#include <cstdlib>
#include "software_renderer.h"

SoftwareRenderer::~SoftwareRenderer() {
    delete [] indices;
}

SoftwareRenderer::SoftwareRenderer() : indices(new unsigned[width * height]{}) {
    for (unsigned x = 0; x < width; x++) {
        indices[x + width * (height - 1)] = 36;
    }
}

void SoftwareRenderer::renderPixels(unsigned *pixels) {
    for (unsigned x = 0; x < width; x++) {
        for (unsigned y = 1; y < height; y++) {
            auto src = x + y * width;
            auto index = indices[src];
            if (index) {
                auto random = rand() % 3;
                auto dst = src - random + 1;
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