#include "PointLight.h"

// Temporary API leak abstraction
#include "OpenGLOmniShadowMap.h"


PointLight::PointLight() : Light() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    constant = 1.0f;
    linear = 0.0f;
    exponent = 0.0f;
}

PointLight::PointLight(unsigned int shadowWidth, unsigned int shadowHeight,
                        float near, float far,
                        float red, float green, float blue,
                        float aIntensity, float dIntensity,
                        float xPos, float yPos, float zPos,
                        float con, float lin, float exp) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity) {

    position = glm::vec3(xPos, yPos, zPos);
    constant = con;
    linear = lin;
    exponent = exp;

    farPlane = far;

    float aspect = (float)shadowWidth/ (float)shadowHeight;
    lightProj = glm::perspective(glm::radians(90.0f), aspect, near, far);

    // Temporary OpenGL abstraction leak
    shadowMap = new OpenGLOmniShadowMap();
    shadowMap->init(shadowWidth, shadowHeight);
}

PointLight::~PointLight() = default;

void PointLight::useLight(IShader& shader, const std::string& prefix) {
    Light::useLight(shader, prefix + ".base");
    shader.setVec3(prefix + ".position", position);
    shader.setFloat(prefix + ".constant", constant);
    shader.setFloat(prefix + ".linear", linear);
    shader.setFloat(prefix + ".exponent", exponent);
}

std::vector<glm::mat4> PointLight::calculateLightTransform() {
    std::vector<glm::mat4> lightMatrices;

    //+x -x
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));

    //+y -y
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));

    //+z -z
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

    return lightMatrices;
}

float PointLight::getFarPlane() {
    return farPlane;
}

glm::vec3 PointLight::getPosition() {
    return position;
}
