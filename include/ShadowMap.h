#pragma once

#include <glad/glad.h>

class ShadowMap {
public:
    ShadowMap();

    virtual ~ShadowMap();


    virtual bool init(GLuint width, GLuint height);

    virtual void write();

    virtual void read(GLenum textureUnit);

    GLuint getShadowWidth();
    GLuint getShadowHeight();

private:
    GLuint FBO, shadowMap;
    GLuint shadowWidth, shadowHeight;
};
