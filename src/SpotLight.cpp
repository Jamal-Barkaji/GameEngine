#include "SpotLight.h"


SpotLight::SpotLight() : PointLight() {
    direction = glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f));
    edge = 0.0f;
    procEdge = cosf(glm::radians(edge));
}

SpotLight::SpotLight(unsigned int shadowWidth, unsigned int shadowHeight,
                    float near, float far,
                    float red, float green, float blue,
                    float aIntensity, float dIntensity,
                    float xPos, float yPos, float zPos,
                    float con, float lin, float exp,
                    float xDir, float yDir, float zDir,
                    float edg) : PointLight(shadowWidth, shadowHeight, near, far, red, green, blue, aIntensity, dIntensity, xPos, yPos, zPos, con, lin, exp) {

    direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
    edge = edg;
    procEdge = cosf(glm::radians(edge));
}

SpotLight::~SpotLight() = default;


void SpotLight::useLight(IShader& shader, const std::string& prefix) {
    PointLight::useLight(shader, prefix + ".base");
    shader.setVec3(prefix + ".direction", direction);
    shader.setFloat(prefix + ".edge", procEdge);
}

void SpotLight::setFlash(glm::vec3 pos, glm::vec3 dir) {
    position = pos;
    direction = dir;
}
