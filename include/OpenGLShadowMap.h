#pragma once

#include <glad/glad.h>

#include "IShadowMap.h"


class OpenGLShadowMap : public IShadowMap {
public:
    OpenGLShadowMap();

    ~OpenGLShadowMap() override;


    virtual bool init(GLuint width, GLuint height) override;

    virtual void write() override;

    virtual void read(GLenum textureUnit) override;

    GLuint getShadowWidth() override;
    GLuint getShadowHeight() override;

protected:
    GLuint FBO, shadowMap;
    GLuint shadowWidth, shadowHeight;
};
