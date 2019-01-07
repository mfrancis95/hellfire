#include <SDL2/SDL.h>

#define PALETTE_SIZE 37

struct Renderer {

    const unsigned *palette;

    virtual ~Renderer() = default;
    virtual void render() = 0;

protected:

    unsigned height, width;
    SDL_Window *window;

    Renderer(SDL_Window *window, const unsigned width, const unsigned height);

};

Renderer *createRenderer(SDL_Window *window, const unsigned width, const unsigned height);