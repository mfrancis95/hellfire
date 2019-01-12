#include <random>
#include "renderer.h"

struct SoftwareRenderer : Renderer {

    virtual ~SoftwareRenderer();
    void extinguish();
    void reset();

protected:

    SoftwareRenderer(
        SDL_Window *window, const unsigned width, const unsigned height
    );
    void renderPixels(unsigned *pixels);

private:

    std::uniform_int_distribution<unsigned> distribution;
    bool extinguishing;
    std::default_random_engine generator;
    unsigned *indices;

};