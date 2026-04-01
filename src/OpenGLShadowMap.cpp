#include "OpenGLShadowMap.h"

#include <iostream>
#include <__msvc_ostream.hpp>


OpenGLShadowMap::OpenGLShadowMap() {
    FBO = 0;
    shadowMap = 0;
}

OpenGLShadowMap::~OpenGLShadowMap() {
    if (FBO) {
        glDeleteFramebuffers(1, &FBO);
    }
    if (shadowMap) {
        glDeleteTextures(1, &shadowMap);
    }
}

bool OpenGLShadowMap::init(GLuint width, GLuint height) {
    shadowWidth = width; shadowHeight = height;

    glGenFramebuffers(1, &FBO);

    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                 nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColour[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer Error:" << status << std::endl;
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

void OpenGLShadowMap::write() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void OpenGLShadowMap::read(GLenum textureUnit) {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
}

GLuint OpenGLShadowMap::getShadowWidth() {
    return shadowWidth;
}

GLuint OpenGLShadowMap::getShadowHeight() {
    return shadowHeight;
}