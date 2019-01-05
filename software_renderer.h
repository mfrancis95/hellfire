#include "renderer.h"

struct SoftwareRenderer : Renderer {

    virtual ~SoftwareRenderer();

protected:

    unsigned *indices;

    SoftwareRenderer();

    void renderPixels(unsigned *pixels);

};