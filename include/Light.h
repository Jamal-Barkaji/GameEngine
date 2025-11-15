#pragma once

#include <glm/glm.hpp>


class Light {
public:
    Light();
    Light(float red, float green, float blue, float aIntensity,
        float xDir, float yDir, float zDir, float dIntensity);

    void useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
                    unsigned int diffuseIntensityLocation, unsigned int directionLocation,
                    unsigned int specularIntensityLocation, unsigned int shininessLocation);

    ~Light();

private:
    glm::vec3 colour;
    float ambientIntensity;

    glm::vec3 direction;
    float diffuseIntensity;
};