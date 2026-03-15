#pragma once

#include "IShader.h"
#include "Light.h"


class DirectionalLight : public Light {
public:
    DirectionalLight();
    DirectionalLight(float shadowWidth, float shadowHeight,
                        float red, float green, float blue,
                        float aIntensity, float dIntensity,
                        float xDir, float yDir, float zDir);

    ~DirectionalLight() override;

    void useLight(IShader& shader) override;

    glm::mat4 calculateLightTransform();

private:
    glm::vec3 direction{};
};