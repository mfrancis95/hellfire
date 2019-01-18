#include "opengl_renderer.h"

struct MappedRenderer : OpenGLRenderer {

    void render() {
        renderPixels(static_cast<unsigned *>(glMapBuffer(
            GL_TEXTURE_BUFFER, GL_WRITE_ONLY
        )));
        glUnmapBuffer(GL_TEXTURE_BUFFER);
        OpenGLRenderer::render();
    }

private:

    MappedRenderer(
        SDL_Window *window, const unsigned width, const unsigned height
    ) : OpenGLRenderer{window, width, height} {
        glBufferStorage(
            GL_TEXTURE_BUFFER, width * height * sizeof(unsigned), nullptr,
            GL_CLIENT_STORAGE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_WRITE_BIT
        );
        glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, buffers[1]);
    }

    friend Renderer *createRenderer(
        SDL_Window *window, const unsigned width, const unsigned height
    );

};

Renderer *createRenderer(
    SDL_Window *window, const unsigned width, const unsigned height
) {
    return new MappedRenderer{window, width, height};
}