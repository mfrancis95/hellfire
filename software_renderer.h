#include "renderer.h"

struct SoftwareRenderer : Renderer {

    virtual ~SoftwareRenderer();

protected:

    SoftwareRenderer(
        SDL_Window *window, const unsigned width, const unsigned height
    );
    void renderPixels(unsigned *pixels);

private:

    unsigned *indices;

};