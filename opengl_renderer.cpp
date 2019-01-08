#define GL_GLEXT_PROTOTYPES

#include <cstdlib>
#include <cstdio>
#include <GL/gl.h>
#include "software_renderer.h"

static char *readFile(const char *file) {
    auto f = fopen(file, "rb");
    fseek(f, 0, SEEK_END);
    auto length = ftell(f);
    fseek(f, 0, SEEK_SET);
    auto data = new char[length + 1];
    fread(data, 1, length, f);
    data[length] = '\0';
    fclose(f);
    return data;
}

static GLuint setupShader(const GLint type, const char *file) {
    auto shader = glCreateShader(type);
    auto shaderSource = readFile(file);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    delete [] shaderSource;
    return shader;
}

struct OpenGLRenderer : SoftwareRenderer {

    ~OpenGLRenderer() {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(program);
        glDeleteTextures(1, &texture);
        glDeleteBuffers(2, buffers);
        glDeleteVertexArrays(1, &vertexArray);
        SDL_GL_DeleteContext(context);
    }

    void render() {
        renderPixels(pixels);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        SDL_GL_SwapWindow(window);
    }

private:

    GLuint buffers[2], fragmentShader, program, texture, vertexArray,
        vertexShader;
    SDL_GLContext context;
    unsigned *pixels;

    OpenGLRenderer(
        SDL_Window *window, const unsigned width, const unsigned height
    ) : SoftwareRenderer{window, width, height} {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        context = SDL_GL_CreateContext(window);
        glFrontFace(GL_CW);
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);
        glGenBuffers(2, buffers);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        GLfloat positionData[8] = {
            -1, -1,
            -1, 1,
            1, -1,
            1, 1
        };
        glBufferData(
            GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW
        );
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_BUFFER, texture);
        glBindBuffer(GL_TEXTURE_BUFFER, buffers[1]);
        glBufferStorage(
            GL_TEXTURE_BUFFER, width * height * sizeof(unsigned), nullptr,
            GL_CLIENT_STORAGE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_WRITE_BIT
        );
        pixels = (unsigned *) glMapBuffer(GL_TEXTURE_BUFFER, GL_WRITE_ONLY);
        glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, buffers[1]);
        glAttachShader(
            program = glCreateProgram(),
            vertexShader = setupShader(GL_VERTEX_SHADER, "shader.vert")
        );
        glAttachShader(
            program,
            fragmentShader = setupShader(GL_FRAGMENT_SHADER, "shader.frag")
        );
        glLinkProgram(program);
        glUseProgram(program);
        int windowHeight, windowWidth;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        glUniform1ui(glGetUniformLocation(program, "scaleX"), windowWidth / width);
        glUniform1ui(glGetUniformLocation(program, "scaleY"), windowHeight / height);
        glUniform1ui(glGetUniformLocation(program, "width"), width);
    }

    friend Renderer *createRenderer(
        SDL_Window *window, const unsigned width, const unsigned height
    );

};

Renderer *createRenderer(
    SDL_Window *window, const unsigned width, const unsigned height
) {
    return new OpenGLRenderer{window, width, height};
}