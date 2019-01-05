#include "software_renderer.h"

struct TextureRenderer : SoftwareRenderer {

    ~TextureRenderer() {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
    }

    void render() {
        int pitch;
        unsigned *pixels;
        SDL_LockTexture(texture, nullptr, (void **) &pixels, &pitch);
        renderPixels(pixels);
        SDL_UnlockTexture(texture);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

private:

    SDL_Renderer *renderer;
    SDL_Texture *texture;

    TextureRenderer() : SoftwareRenderer{} {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        texture = SDL_CreateTexture(
            renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING,
            width, height
        );
    }

    friend Renderer *getRenderer();

};

Renderer *getRenderer() {
    return new TextureRenderer;
}