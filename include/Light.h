#pragma once

#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "IShader.h"
#include "OpenGLShadowMap.h"


class Light {
public:
    Light();
    Light(unsigned int shadowWidth, unsigned int shadowHeight,
            float red, float green, float blue,
            float aIntensity, float dIntensity);

    virtual ~Light();

    OpenGLShadowMap* getShadowMap();

    virtual void useLight(IShader& shader, const std::string& prefix) = 0;

protected:
    glm::vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;

    glm::mat4 lightProj;

    OpenGLShadowMap* shadowMap;
};