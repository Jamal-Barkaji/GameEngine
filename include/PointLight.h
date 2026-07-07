#pragma once

#include "Light.h"


class PointLight : public Light {
public:
    PointLight();
    PointLight(unsigned int shadowWidth, unsigned int shadowHeight,
                float near, float far,
                float red, float green, float blue,
                float aIntensity, float dIntensity,
                float xPos, float yPos, float zPos,
                float con, float lin, float exp);

    ~PointLight() override;

    void useLight(IShader& shader, const std::string& prefix) override;

    std::vector<glm::mat4> calculateLightTransform();

    float getFarPlane();
    glm::vec3 getPosition();

protected:
    glm::vec3 position;

    float constant, linear, exponent;

    float farPlane;
};