#include "DirectionalLight.h"


DirectionalLight::DirectionalLight() : Light() {
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

DirectionalLight::DirectionalLight(float shadowWidth, float shadowHeight,
                                    float red, float green, float blue,
                                    float aIntensity, float dIntensity,
                                    float xDir, float yDir, float zDir) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity) {

    direction = glm::vec3(xDir, yDir, zDir);
    lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

DirectionalLight::~DirectionalLight() = default;


void DirectionalLight::useLight(IShader& shader, const std::string& prefix) {
    Light::useLight(shader, prefix + ".base");
    shader.setVec3(prefix + ".direction", direction);
}

glm::mat4 DirectionalLight::calculateLightTransform() {
    return lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
