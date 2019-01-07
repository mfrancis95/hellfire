#include <cstdlib>
#include "software_renderer.h"

SoftwareRenderer::~SoftwareRenderer() {
    delete [] indices;
}

SoftwareRenderer::SoftwareRenderer(
    SDL_Window *window, unsigned width, unsigned height
) : Renderer{window, width, height}, indices(new unsigned[width * height]{}) {
    for (auto x = 0U; x < width; x++) {
        indices[x + width * (height - 1)] = PALETTE_SIZE - 1;
    }
}

void SoftwareRenderer::renderPixels(unsigned *pixels) {
    for (auto x = 0U; x < width; x++) {
        for (auto y = 1U; y < height; y++) {
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