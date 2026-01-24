#include "Light.h"

#include <glad/glad.h>


Light::Light() {
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;
    diffuseIntensity = 0.0f;
}

Light::Light(GLfloat shadowWidth, GLfloat shadowHeight, GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity) {
    shadowMap = new ShadowMap();
    shadowMap->init(shadowWidth, shadowHeight);

    colour = glm::vec3(red, green, blue);
    ambientIntensity = aIntensity;
    diffuseIntensity = dIntensity;
}

Light::~Light() {}

ShadowMap* Light::getShadowMap() {
    return shadowMap;
}


//void Light::useLight(float ambientIntensityLocation, float ambientColourLocation) {
//    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
//    glUniform1f(ambientIntensityLocation, ambientIntensity);
//}
