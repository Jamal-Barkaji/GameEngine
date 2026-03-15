#include "PointLight.h"

#include <glad/glad.h>


PointLight::PointLight() : Light() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    constant = 1.0f;
    linear = 0.0f;
    exponent = 0.0f;
}

PointLight::PointLight(float red, float green, float blue,
                         float aIntensity, float dIntensity,
                         float xPos, float yPos, float zPos,
                         float con, float lin, float exp) : Light(1024, 1024, red, green, blue, aIntensity, dIntensity) {

    position = glm::vec3(xPos, yPos, zPos);
    constant = con;
    linear = lin;
    exponent = exp;
}

PointLight::~PointLight() = default;

void PointLight::useLight(IShader& shader) {
    Light::useLight(shader);
    shader.setVec3("PointLight.position", position);
    shader.setFloat("PointLight.constant", constant);
    shader.setFloat("PointLight.linear", linear);
    shader.setFloat("PointLight.exponent", exponent);
}

// void PointLight::useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
//                           unsigned int diffuseIntensityLocation, unsigned int positionLocation,
//                           unsigned int constantLocation, unsigned int linearLocation,
//                           unsigned int exponentLocation) {
//
//     glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
//     glUniform1f(ambientIntensityLocation, ambientIntensity);
//     glUniform1f(diffuseIntensityLocation, diffuseIntensity);
//
//     glUniform3f(positionLocation, position.x, position.y, position.z);
//
//
//     glUniform1f(constantLocation, constant);
//     glUniform1f(linearLocation, linear);
//     glUniform1f(exponentLocation, exponent);
// }
