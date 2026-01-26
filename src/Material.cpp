#include "Material.h"


Material::Material() {
    specularIntensity = 0.0f;
    shininess = 0.0f;
}

Material::Material(GLfloat sIntensity, GLfloat shine) {
    specularIntensity = sIntensity;
    shininess = shine;
}

Material::~Material() {

}

void Material::bind(Shader& shader) const
{
    if (albedoMap)
    {
        glActiveTexture(GL_TEXTURE0);
        albedoMap->useTexture();
        glUniform1i(shader.getAlbedoLocation(), 0);
    }

    glUniform1f(shader.getSpecularIntensityLocation(), specularIntensity);
    glUniform1f(shader.getShininessLocation(), shininess);
}

// void Material::useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation) {
//     glUniform1f(specularIntensityLocation, specularIntensity);
//     glUniform1f(shininessLocation, shininess);
//
//     albedoMap->useTexture();
// }