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
    if (albedoMap) {
        albedoMap->bindTexture(0);
        shader.setInt("material.albedoMap", 0);
        shader.setInt("theTexture", 0);
    }
    shader.setFloat("material.specularIntensity", specularIntensity);
    shader.setFloat("material.shininess", shininess);
}