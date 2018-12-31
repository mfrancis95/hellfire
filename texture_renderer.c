#include "renderer.h"
#include "software_renderer.h"

static const unsigned int height = 480;
static const unsigned int width = 640;

static unsigned *indices;
static SDL_Renderer *renderer;
static SDL_Texture *texture;

void cleanupRenderer(void) {
    free(indices);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
}

void initRenderer(void) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
    indices = calloc(width * height, sizeof(unsigned));
    for (int x = 0; x < width; x++) {
        indices[x + width * (height - 1)] = 36;
    }
}

void render(void) {
    unsigned pitch;
    unsigned *pixels;
    SDL_LockTexture(texture, NULL, (void **) &pixels, &pitch);
    renderPixels(indices, pixels, width, height);
    SDL_UnlockTexture(texture);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}