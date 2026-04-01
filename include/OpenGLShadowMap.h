#pragma once

#include <glad/glad.h>

#include "IShadowMap.h"


class OpenGLShadowMap : public IShadowMap {
public:
    OpenGLShadowMap();

    ~OpenGLShadowMap() override;


    bool init(GLuint width, GLuint height) override;

    void write() override;

    void read(GLenum textureUnit) override;

    GLuint getShadowWidth() override;
    GLuint getShadowHeight() override;

private:
    GLuint FBO, shadowMap;
    GLuint shadowWidth, shadowHeight;
};
