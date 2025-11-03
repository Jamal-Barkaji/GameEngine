#pragma once

#include <glm/glm.hpp>


class Light {
public:
    Light();
    Light(float red, float green, float blue, float aIntensity);

    void useLight(float ambientIntensityLocation, float ambientColourLocation);

    ~Light();

private:
    glm::vec3 colour;
    float ambientIntensity;
};