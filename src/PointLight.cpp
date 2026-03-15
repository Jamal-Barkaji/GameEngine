#include "PointLight.h"


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

void PointLight::useLight(IShader& shader, const std::string& prefix) {
    Light::useLight(shader, prefix + ".base");
    shader.setVec3(prefix + ".position", position);
    shader.setFloat(prefix + ".constant", constant);
    shader.setFloat(prefix + ".linear", linear);
    shader.setFloat(prefix + ".exponent", exponent);
}
