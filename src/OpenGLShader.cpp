#include "OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>


OpenGLShader::OpenGLShader() {
    shaderID = 0;
    uniformProjection = 0;
    uniformModel = 0;
    uniformView = 0;

    pointLightCount = 0;
    spotLightCount = 0;
}

OpenGLShader::~OpenGLShader() {

}

void OpenGLShader::setInt(const std::string& name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void OpenGLShader::setFloat(const std::string& name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void OpenGLShader::setVec3(const std::string& name, const glm::vec3& value) {
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

int OpenGLShader::getUniformLocation(const std::string& name) {
    if (locationCache.find(name) != locationCache.end())
        return locationCache[name];

    int location = glGetUniformLocation(shaderID, name.c_str());
    locationCache[name] = location;
    return location;
}

void OpenGLShader::createFromString(const char* vertexCode, const char* fragmentCode) {
    compileShader(vertexCode, fragmentCode);
}

void OpenGLShader::createFromFiles(const char* vertexLocation, const char* fragmentLocation) {
    std::string vertexString = readFile(vertexLocation);
    std::string fragmentString = readFile(fragmentLocation);
    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    compileShader(vertexCode, fragmentCode);
}

void OpenGLShader::createFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation) {
    std::string vertexString = readFile(vertexLocation);
    std::string geometryString = readFile(geometryLocation);
    std::string fragmentString = readFile(fragmentLocation);

    const char* vertexCode = vertexString.c_str();
    const char* geometryCode = geometryString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    compileShader(vertexCode, geometryCode, fragmentCode);
}

std::string OpenGLShader::readFile(const char* fileLocation) {
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

void OpenGLShader::compileShader(const char* vertexCode, const char* fragmentCode) {
    shaderID = glCreateProgram();

    if (!shaderID) {
        std::cerr << "Failed to create shader\n";
        return;
    }

    addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    compileProgram();
}

void OpenGLShader::compileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode) {
    shaderID = glCreateProgram();

    if (!shaderID) {
        std::cerr << "Failed to create shader\n";
        return;
    }

    addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    addShader(shaderID, geometryCode, GL_GEOMETRY_SHADER);
    addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    compileProgram();
}

void OpenGLShader::compileProgram() {

    GLint result = 0;
    GLchar elog[1024] = {0};

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(elog), NULL, elog);
        std::cerr << "Failed to link shader:\n" << elog << "\n";
        return;
    }

    //glValidateProgram(shaderID);
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

    // Point Lights
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

    // Spotlights
    uniformSpotLightCount = glGetUniformLocation(shaderID, "spotLightCount");

    for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++) {
        char locBuff[100] = {'\0'};

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.colour", i);
        uniformSpotLight[i].uniformColour = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
        uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
        uniformSpotLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
        uniformSpotLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
        uniformSpotLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
        uniformSpotLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
        uniformSpotLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
        uniformSpotLight[i].uniformDirection = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
        uniformSpotLight[i].uniformEdge = glGetUniformLocation(shaderID, locBuff);
    }
    // Shadows
    uniformTexture = glGetUniformLocation(shaderID, "theTexture");
    uniformDirectionalLightTransform = glGetUniformLocation(shaderID, "directionalLightTransform");
    uniformDirectionalShadowMap = glGetUniformLocation(shaderID, "directionalShadowMap");

    uniformOmniLightPos = glGetUniformLocation(shaderID, "lightPos");
    uniformFarPlane = glGetUniformLocation(shaderID, "farPlane");

    for (size_t i = 0; i < 6; i++) {
        char locBuff[100] = {'\0'};

        snprintf(locBuff, sizeof(locBuff), "lightMatrices[%zu]", i);
        uniformLightMatrices[i] = glGetUniformLocation(shaderID, locBuff);
    }
}

// GLuint OpenGLShader::getProjectLocation() {
//     return uniformProjection;
// }
//
// GLuint OpenGLShader::getModelLocation() {
//     return uniformModel;
// }
//
// GLuint OpenGLShader::getViewLocation() {
//     return uniformView;
// }
//
// GLuint OpenGLShader::getAmbientColourLocation() {
//     return uniformDirectionalLight.uniformColour;
// }
//
// GLuint OpenGLShader::getAmbientIntensityLocation() {
//     return uniformDirectionalLight.uniformAmbientIntensity;
// }
//
// GLuint OpenGLShader::getDiffuseIntensityLocation() {
//     return uniformDirectionalLight.uniformDiffuseIntensity;
// }
//
// GLuint OpenGLShader::getDirectionLocation() {
//     return uniformDirectionalLight.uniformDirection;
// }
//
// GLuint OpenGLShader::getSpecularIntensityLocation() {
//     return uniformSpecularIntensity;
// }
//
// GLuint OpenGLShader::getShininessLocation() {
//     return uniformShininess;
// }
//
// GLuint OpenGLShader::getAlbedoLocation() {
//     return glGetUniformLocation(shaderID, "material.albedoMap");
// }
//
// GLuint OpenGLShader::getEyePositionLocation() {
//     return uniformEyePosition;
// }

// void OpenGLShader::setDirectionalLight(DirectionalLight* dLight) {
//     dLight->useLight(uniformDirectionalLight.uniformAmbientIntensity,
//                      uniformDirectionalLight.uniformColour,
//                      uniformDirectionalLight.uniformDiffuseIntensity,
//                      uniformDirectionalLight.uniformDirection);
// }

// void OpenGLShader::setPointLights(PointLight* pLight, unsigned int lightCount) {
//     if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;
//
//     glUniform1i(uniformPointLightCount, lightCount);
//
//     for (size_t i = 0; i < lightCount; i++)
//         pLight[i].useLight(uniformPointLight[i].uniformAmbientIntensity,
//                              uniformPointLight[i].uniformColour,
//                              uniformPointLight[i].uniformDiffuseIntensity,
//                              uniformPointLight[i].uniformPosition,
//                              uniformPointLight[i].uniformConstant,
//                              uniformPointLight[i].uniformLinear,
//                              uniformPointLight[i].uniformExponent);
// }

// void OpenGLShader::setSpotLights(SpotLight* sLight, unsigned int lightCount) {
//     if (lightCount > MAX_SPOT_LIGHTS) lightCount = MAX_SPOT_LIGHTS;
//
//     glUniform1i(uniformSpotLightCount, lightCount);
//
//     for (size_t i = 0; i < lightCount; i++)
//         sLight[i].useLight(uniformSpotLight[i].uniformAmbientIntensity,
//                              uniformSpotLight[i].uniformColour,
//                              uniformSpotLight[i].uniformDiffuseIntensity,
//                              uniformSpotLight[i].uniformPosition,
//                              uniformSpotLight[i].uniformConstant,
//                              uniformSpotLight[i].uniformLinear,
//                              uniformSpotLight[i].uniformExponent,
//                              uniformSpotLight[i].uniformDirection,
//                              uniformSpotLight[i].uniformEdge);
// }

// void OpenGLShader::setTexture(GLuint textureUnit) {
//     glUniform1i(uniformTexture, textureUnit);
// }
//
// void OpenGLShader::setDirectionalShadowMap(GLuint textureUnit) {
//     glUniform1i(uniformDirectionalShadowMap, textureUnit);
// }
//
// void OpenGLShader::setDirectionalLightTransform(glm::mat4* lTransform) {
//     glUniformMatrix4fv(uniformDirectionalLightTransform, 1, GL_FALSE, glm::value_ptr(*lTransform));
// }

void OpenGLShader::bindShader() const {
    if (shaderID != 0) {
        glUseProgram(shaderID);
    }
}

void OpenGLShader::unbindShader() const {
    glUseProgram(0); 
}

void OpenGLShader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    glShaderSource(theShader, 1, &shaderCode, nullptr);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar elog[1024] = {0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(elog), nullptr, elog);
        std::cerr << "Error compiling shader type " << shaderType << ":\n" << elog << '\n';
        std::cout << "Shader Code being compiled:\n" << shaderCode << std::endl;
        return;
    }

    glAttachShader(theProgram, theShader);
}
