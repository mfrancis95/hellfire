#include <fstream>
#include "opengl_renderer.h"

static const char *readFile(const char *file) {
    std::ifstream stream{file, std::ios::ate};
    std::streamoff length = stream.tellg();
    stream.seekg(0, std::ios::beg);
    auto data = new char[length + 1];
    stream.read(data, length);
    data[length] = '\0';
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

OpenGLRenderer::~OpenGLRenderer() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);
    glDeleteTextures(1, &texture);
    glDeleteBuffers(2, buffers);
    glDeleteVertexArrays(1, &vertexArray);
    SDL_GL_DeleteContext(context);
}

void OpenGLRenderer::render() {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    SDL_GL_SwapWindow(window);
}

OpenGLRenderer::OpenGLRenderer(
    SDL_Window *window, const unsigned width, const unsigned height
) : SoftwareRenderer{window, width, height} {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    context = SDL_GL_CreateContext(window);
    glFrontFace(GL_CW);
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    GLbyte positionData[8] = {
        -1, -1,
        -1, 1,
        1, -1,
        1, 1
    };
    glBufferStorage(
        GL_ARRAY_BUFFER, sizeof(positionData), positionData, 0
    );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_BYTE, GL_FALSE, 0, nullptr);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_BUFFER, texture);
    glBindBuffer(GL_TEXTURE_BUFFER, buffers[1]);
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