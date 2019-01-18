#include "opengl_renderer.h"

struct SubDataRenderer : OpenGLRenderer {

    ~SubDataRenderer() {
        delete [] pixels;
    }

    void render() {
        renderPixels(pixels);
        glBufferSubData(
            GL_TEXTURE_BUFFER, 0, width * height * sizeof(unsigned), pixels
        );
        OpenGLRenderer::render();
    }

private:

    unsigned *pixels;

    SubDataRenderer(
        SDL_Window *window, const unsigned width, const unsigned height
    ) : OpenGLRenderer{window, width, height} {
        glBufferStorage(
            GL_TEXTURE_BUFFER, width * height * sizeof(unsigned), nullptr,
            GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT
        );
        glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, buffers[1]);
        pixels = new unsigned[width * height];
    }

    friend Renderer *createRenderer(
        SDL_Window *window, const unsigned width, const unsigned height
    );

};

Renderer *createRenderer(
    SDL_Window *window, const unsigned width, const unsigned height
) {
    return new SubDataRenderer{window, width, height};
}