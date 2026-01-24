#pragma once

#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "ShadowMap.h"


class Light {
public:
    Light();
    Light(GLfloat shadowWidth, GLfloat shadowHeight,
            GLfloat red, GLfloat green, GLfloat blue,
            GLfloat aIntensity, GLfloat dIntensity);

    virtual ~Light();

    ShadowMap* getShadowMap();

    //virtual void useLight(float ambientIntensityLocation, float ambientColourLocation);

protected:
    glm::vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;

    glm::mat4 lightProj;

    ShadowMap* shadowMap;
};