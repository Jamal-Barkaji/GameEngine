#pragma once

#include "Light.h"


class PointLight : public Light {
public:
    PointLight();
    PointLight(float red, float green, float blue,
                float aIntensity, float dIntensity,
                float xPos, float yPos, float zPos,
                float con, float lin, float exp);

    ~PointLight() override;

    // void useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
    //                 unsigned int diffuseIntensityLocation, unsigned int positionLocation,
    //                 unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation);

    void useLight(IShader& shader) override;

protected:
    glm::vec3 position;

    float constant, linear, exponent;
};