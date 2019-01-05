#include <SDL2/SDL.h>

extern const unsigned height, palette[37], width;

extern SDL_Window *window;

struct Renderer {

    virtual ~Renderer() = default;
    virtual void render() = 0;

};

Renderer *getRenderer();