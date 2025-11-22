#include "Light.h"

#include <glad/glad.h>


Light::Light() {
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;
    diffuseIntensity = 0.0f;
}

Light::Light(float red, float green, float blue, float aIntensity, float dIntensity) {
    colour = glm::vec3(red, green, blue);
    ambientIntensity = aIntensity;
    diffuseIntensity = dIntensity;
}

Light::~Light() {}

//void Light::useLight(float ambientIntensityLocation, float ambientColourLocation) {
//    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
//    glUniform1f(ambientIntensityLocation, ambientIntensity);
//}
