#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include "software_renderer.h"

struct OpenGLRenderer : SoftwareRenderer {

    virtual ~OpenGLRenderer();

    void render();

protected:

    GLuint buffers[2];

    OpenGLRenderer(
        SDL_Window *window, const unsigned width, const unsigned height
    );

private:

    SDL_GLContext context;
    GLuint fragmentShader, program, texture, vertexArray, vertexShader;

};