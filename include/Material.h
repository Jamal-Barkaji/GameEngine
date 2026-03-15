#pragma once

#include <glad/glad.h>

#include "OpenGLTexture.h"
#include "OpenGLShader.h"


class Material {
public:
    Material();
    Material(float sIntensity, float shine);

    ~Material();

    void bindMaterial(IShader& shader) const;


    std::shared_ptr<ITexture> albedoMap;

private:
    float specularIntensity;
    float shininess;
};