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

// void DirectionalLight::useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
//                         unsigned int diffuseIntensityLocation, unsigned int directionLocation) {
//
//     glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
//     glUniform1f(ambientIntensityLocation, ambientIntensity);
//
//     glUniform3f(directionLocation, direction.x, direction.y, direction.z);
//     glUniform1f(diffuseIntensityLocation, diffuseIntensity);
// }

void DirectionalLight::useLight(IShader& shader) {
    Light::useLight(shader);
    shader.setVec3("DirectionalLight.direction", direction);
}

glm::mat4 DirectionalLight::calculateLightTransform() {
    return lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
