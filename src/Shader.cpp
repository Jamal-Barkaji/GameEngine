#include "Shader.h"

std::string Shader::vShader = ReadFile("C:\\Users\\barka\\CLionProjects\\GameEngine\\Shaders\\shader.vert");

std::string Shader::fShader = ReadFile("C:\\Users\\barka\\CLionProjects\\GameEngine\\Shaders\\shader.frag");

///////////////////////////////////////////////////////


Shader::Shader() {
    shaderID = 0;
    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;

    CreateFromString(vShader.c_str(), fShader.c_str());
}

Shader::~Shader() {

}


void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
    CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation) {
    std::string vertexString = ReadFile(vertexLocation);
    std::string fragmentString = ReadFile(fragmentLocation);
    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation) {
    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Failed to read file " << fileLocation << "\n";
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
    std::getline(fileStream, line);
    content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {
    shaderID = glCreateProgram();

    if (!shaderID) {
        std::cerr << "Failed to create shader\n";
        return;
    }

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar elog[1024] = {0};

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(elog), NULL, elog);
        std::cerr << "Failed to link shader:\n" << elog << "\n";
        return;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(elog), NULL, elog);
        std::cerr << "Failed to validate shader:\n" << elog << "\n";
        return;
    }

    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformAmbientColour = glGetUniformLocation(shaderID, "directionalLight.colour");
    uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
}

GLuint Shader::GetProjectLocation() {
    return uniformProjection;
}

GLuint Shader::GetModelLocation() {
    return uniformModel;
}

GLuint Shader::GetViewLocation() {
    return uniformView;
}

GLuint Shader::getAmbientColourLocation() {
    return uniformAmbientColour;
}

GLuint Shader::getAmbientIntensityLocation() {
    return uniformAmbientIntensity;
}


void Shader::UseShader() {
    if (shaderID != 0) {
        glUseProgram(shaderID);
    }
}

void Shader::ClearShader() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

    uniformModel = 0;
    uniformProjection = 0;
}


void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
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
