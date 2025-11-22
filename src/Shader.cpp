#include "Shader.h"

std::string Shader::vShader = ReadFile("C:\\Users\\barka\\CLionProjects\\GameEngine\\Shaders\\shader.vert");

std::string Shader::fShader = ReadFile("C:\\Users\\barka\\CLionProjects\\GameEngine\\Shaders\\shader.frag");

///////////////////////////////////////////////////////


Shader::Shader() {
    shaderID = 0;
    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;

    pointLightCount = 0;

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
    uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
    uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
    uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
    uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
    uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

    uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");

    for (size_t i = 0; i < MAX_POINT_LIGHTS; i++) {
        char locBuff[100] = {'\0'};

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.colour", i);
        uniformPointLight[i].uniformColour = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
        uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
        uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
        uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
        uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
        uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
        uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);
    }
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
    return uniformDirectionalLight.uniformColour;
}

GLuint Shader::getAmbientIntensityLocation() {
    return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::getDiffuseIntensityLocation() {
    return uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::getDirectionLocation() {
    return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::getSpecularIntensityLocation() {
    return uniformSpecularIntensity;
}

GLuint Shader::getShininessLocation() {
    return uniformShininess;
}

GLuint Shader::getEyePositionLocation() {
    return uniformEyePosition;
}

void Shader::setDirectionalLight(DirectionalLight* dLight) {
    dLight->useLight(uniformDirectionalLight.uniformAmbientIntensity,
                     uniformDirectionalLight.uniformColour,
                     uniformDirectionalLight.uniformDiffuseIntensity,
                     uniformDirectionalLight.uniformDirection);
}

void Shader::setPointLights(PointLight* pLight, unsigned int lightCount) {
    if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

    glUniform1i(uniformPointLightCount, lightCount);

    for (size_t i = 0; i < lightCount; i++)
        pLight[i].useLight(uniformPointLight[i].uniformAmbientIntensity,
                             uniformPointLight[i].uniformColour,
                             uniformPointLight[i].uniformDiffuseIntensity,
                             uniformPointLight[i].uniformPosition,
                             uniformPointLight[i].uniformConstant,
                             uniformPointLight[i].uniformLinear,
                             uniformPointLight[i].uniformExponent);

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
