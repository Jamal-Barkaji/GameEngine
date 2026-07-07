#pragma once

#include "PointLight.h"


class SpotLight : public PointLight {
public:
    SpotLight();
    SpotLight(unsigned int shadowWidth, unsigned int shadowHeight,
            float near, float far,
            float red, float green, float blue,
            float aIntensity, float dIntensity,
            float xPos, float yPos, float zPos,
            float con, float lin, float exp,
            float xDir, float yDir, float zDir,
            float edg);

    ~SpotLight() override;

    void useLight(IShader& shader, const std::string& prefix) override;

    void setFlash(glm::vec3 pos, glm::vec3 dir);

private:
    glm::vec3 direction;

    float edge, procEdge;
};