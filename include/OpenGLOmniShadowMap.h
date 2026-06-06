#pragma once
#include "OpenGLShadowMap.h"


class OpenGLOmniShadowMap : public OpenGLShadowMap {
public:
    OpenGLOmniShadowMap();
    ~OpenGLOmniShadowMap();

    bool init(GLuint width, GLuint height) override;

    void write() override;

    void read(GLenum textureUnit) override;
};
