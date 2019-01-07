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

    SurfaceRenderer(
        SDL_Window *window, const unsigned width, const unsigned height
    ) : SoftwareRenderer{window, width, height} {
        surface = SDL_CreateRGBSurfaceWithFormat(
            0, width, height, 24, SDL_PIXELFORMAT_RGB888
        );
    }

    friend Renderer *createRenderer(
        SDL_Window *window, const unsigned width, const unsigned height
    );

};

Renderer *createRenderer(
    SDL_Window *window, const unsigned width, const unsigned height
) {
    return new SurfaceRenderer{window, width, height};
}