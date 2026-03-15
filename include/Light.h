#pragma once

#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "IShader.h"
#include "ShadowMap.h"


class Light {
public:
    Light();
    Light(float shadowWidth, float shadowHeight,
            float red, float green, float blue,
            float aIntensity, float dIntensity);

    virtual ~Light();

    ShadowMap* getShadowMap();

    virtual void useLight(IShader& shader) = 0;

protected:
    glm::vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;

    glm::mat4 lightProj;

    ShadowMap* shadowMap;
};