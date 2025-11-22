#pragma once

#include "Light.h"


class DirectionalLight : public Light {
public:
    DirectionalLight();
    DirectionalLight(float red, float green, float blue,
                        float aIntensity, float dIntensity,
                        float xDir, float yDir, float zDir);

    ~DirectionalLight();

    void useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
                    unsigned int diffuseIntensityLocation, unsigned int directionLocation);

private:
    glm::vec3 direction{};
};