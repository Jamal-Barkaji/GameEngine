#include "DirectionalLight.h"


DirectionalLight::DirectionalLight() : Light() {
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    lightProj = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 0.1f, 150.0f);
}

DirectionalLight::DirectionalLight(unsigned int shadowWidth, unsigned int shadowHeight,
                                    float red, float green, float blue,
                                    float aIntensity, float dIntensity,
                                    float xDir, float yDir, float zDir) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity) {

    direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
    // TODO: The orthographic projection parameters should ideally calculate this frustum dynamically based on the player's camera position (Cascaded Shadow Maps)
    lightProj = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 0.1f, 150.0f);
}

DirectionalLight::~DirectionalLight() = default;


void DirectionalLight::useLight(IShader& shader, const std::string& prefix) {
    Light::useLight(shader, prefix + ".base");
    shader.setVec3(prefix + ".direction", direction);
}

glm::mat4 DirectionalLight::calculateLightTransform() {
    // TODO: This is a very basic implementation. It assumes the light is always pointing towards the origin and is 50 units away. In a real application, you would want to calculate this based on the scene's bounds and the light's direction.
    glm::vec3 lightPos = -direction * 50.0f;  // Distance of 50 units from origin
    glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    return lightProj * lightView;
}
