#include "software_renderer.h"

struct SurfaceRenderer : SoftwareRenderer {

    ~SurfaceRenderer() {
        SDL_FreeSurface(surface);
    }

    void render() {
        renderPixels((unsigned *) surface->pixels);
        SDL_BlitScaled(surface, nullptr, SDL_GetWindowSurface(window), nullptr);
        SDL_UpdateWindowSurface(window);
    }

private:

    SDL_Surface *surface;

    SurfaceRenderer() : SoftwareRenderer{} {
        surface = SDL_CreateRGBSurfaceWithFormat(
            0, width, height, 24, SDL_PIXELFORMAT_RGB888
        );
    }

    friend Renderer *getRenderer();

};

Renderer *getRenderer() {
    return new SurfaceRenderer;
}