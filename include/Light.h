#pragma once

#include <glm/glm.hpp>


class Light {
public:
    Light();
    Light(float red, float green, float blue,
            float aIntensity, float dIntensity);

    //virtual void useLight(float ambientIntensityLocation, float ambientColourLocation);

    virtual ~Light();

protected:
    glm::vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
};