#pragma once

#include <glad/glad.h>

#include "Texture.h"
#include "Shader.h"


class Material {
public:
    Material();
    Material(GLfloat sIntensity, GLfloat shine);

    ~Material();

    void bind(Shader& shader) const;

    // void useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

    std::shared_ptr<Texture> albedoMap;

private:
    GLfloat specularIntensity;
    GLfloat shininess;
};