#include <stdlib.h>
#include "renderer.h"

static const unsigned int height = 480;
static const unsigned int width = 640;

static unsigned *indices;
static SDL_Surface *surface;

void cleanupRenderer(void) {
    free(indices);
    SDL_FreeSurface(surface);
}

void initRenderer(void) {
    surface = SDL_CreateRGBSurface(0, width, height, 32, 0xFF0000, 0x00FF00, 0x0000FF, 0);
    indices = calloc(width * height, sizeof(unsigned));
    for (int x = 0; x < width; x++) {
        indices[x + width * (height - 1)] = 36;
    }
}

void render(void) {
    unsigned *pixels = surface->pixels;
    for (int x = 0; x < width; x++) {
        for (int y = 1; y < height; y++) {
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
    SDL_BlitScaled(surface, NULL, SDL_GetWindowSurface(window), NULL);
    SDL_UpdateWindowSurface(window);
}