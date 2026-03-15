#include "Material.h"


Material::Material() {
    specularIntensity = 0.0f;
    shininess = 0.0f;
}

Material::Material(float sIntensity, float shine) {
    specularIntensity = sIntensity;
    shininess = shine;
}

Material::~Material() {

}

void Material::bindMaterial(IShader& shader) const {
    if (albedoMap)
    {
        glActiveTexture(GL_TEXTURE0);
        albedoMap->bindTexture();

        shader.setInt("Material.albedoMap", 0);
    }

    shader.setFloat("Material.specularIntensity", specularIntensity);
    shader.setFloat("Material.shininess", shininess);
}
