#include "Light.h"


Light::Light() {
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;
    diffuseIntensity = 0.0f;
}

Light::Light(float shadowWidth, float shadowHeight, float red, float green, float blue, float aIntensity, float dIntensity) {
    shadowMap = new ShadowMap();
    shadowMap->init(shadowWidth, shadowHeight);

    colour = glm::vec3(red, green, blue);
    ambientIntensity = aIntensity;
    diffuseIntensity = dIntensity;
}

Light::~Light() = default;


ShadowMap* Light::getShadowMap() {
    return shadowMap;
}

void Light::useLight(IShader& shader, const std::string& prefix) {
    shader.setVec3(prefix + ".colour", colour);
    shader.setFloat(prefix + ".ambientIntensity", ambientIntensity);
    shader.setFloat(prefix + ".diffuseIntensity", diffuseIntensity);
    shader.setMat4(prefix + ".lightProj", lightProj);
}