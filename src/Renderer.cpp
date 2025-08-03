#include "Renderer.h"
#include <iostream>


const char* Renderer::vShader = R"(
    #version 330

    layout (location = 0) in vec3 pos;

    out vec4 vCol;

    uniform mat4 model;

    void main() {
    gl_Position = model * vec4(pos, 1.0);
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
    }
)";

const char* Renderer::fShader = R"(
    #version 330

    in vec4 vCol;

    out vec4 colour;

    void main() {
    colour = vCol;
    }
)";

//////////////////////////////////////////////////////////////////////

Renderer::Renderer() {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }
    CreateTriangle();
    CompileShaders();
}

Renderer::~Renderer() {

}

void Renderer::CreateTriangle() {
    GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
}

void Renderer::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    glShaderSource(theShader, 1, &shaderCode, nullptr);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar elog[1024] = {0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(elog), nullptr, elog);
        std::cerr << "Error compiling shader type " << shaderType << ":\n" << elog << '\n';
        return;
    }

    glAttachShader(theProgram, theShader);
}


void Renderer::CompileShaders() {
    shader = glCreateProgram();

    if (!shader) {
        std::cerr << "Failed to create shader\n";
        return;
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar elog[1024] = {0};

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(elog), NULL, elog);
        std::cerr << "Failed to link shader:\n" << elog << "\n";
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(elog), NULL, elog);
        std::cerr << "Failed to validate shader:\n" << elog << "\n";
        return;
    }

    uniformModel = glGetUniformLocation(shader, "model");
}

void Renderer::Render(Transformer& transformer) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);

        /*
         *
         * **/
        glm::mat4 model = transformer.getModelMatrix();
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

    glUseProgram(0);
}
