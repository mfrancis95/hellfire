#include "renderer.h"
#include "software_renderer.h"

static const unsigned height = 480;
static const unsigned width = 640;

static unsigned *indices;
static SDL_Surface *surface;

void cleanupRenderer(void) {
    free(indices);
    SDL_FreeSurface(surface);
}

void initRenderer(void) {
    surface = SDL_CreateRGBSurfaceWithFormat(
        0, width, height, 24, SDL_PIXELFORMAT_RGB888
    );
    indices = calloc(width * height, sizeof(unsigned));
    for (unsigned x = 0; x < width; x++) {
        indices[x + width * (height - 1)] = 36;
    }
}

void render(void) {
    renderPixels(indices, surface->pixels, width, height);
    SDL_BlitScaled(surface, NULL, SDL_GetWindowSurface(window), NULL);
    SDL_UpdateWindowSurface(window);
}