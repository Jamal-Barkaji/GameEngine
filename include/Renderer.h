#pragma once

#include <glad/glad.h>
#include <SDL.h>
#include <string.h>
#include <Transformer.h>


class Renderer {
public:
    Renderer();
    ~Renderer();

    void CreateTriangle();
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    void CompileShaders();
    void Render(Transformer& transformer);

private:
    GLuint VAO, VBO, shader;
    GLint uniformModel;
    static const char* vShader;
    static const char* fShader;

};
