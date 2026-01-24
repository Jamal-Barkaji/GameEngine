#pragma once

#include "Light.h"


class DirectionalLight : public Light {
public:
    DirectionalLight();
    DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight,
                        GLfloat red, GLfloat green, GLfloat blue,
                        GLfloat aIntensity, GLfloat dIntensity,
                        GLfloat xDir, GLfloat yDir, GLfloat zDir);

    ~DirectionalLight();

    void useLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
                    unsigned int diffuseIntensityLocation, unsigned int directionLocation);

    glm::mat4 calculateLightTransform();

private:
    glm::vec3 direction{};
};