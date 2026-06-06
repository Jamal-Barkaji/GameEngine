#include "OpenGLShadowMap.h"

#include <iostream>


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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                 nullptr);
    GLfloat borderColour[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer Error: " << status << std::endl;
        std::cerr << "GL_FRAMEBUFFER_COMPLETE = " << GL_FRAMEBUFFER_COMPLETE << std::endl;
        if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT) {
            std::cerr << "Reason: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << std::endl;
        } else if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT) {
            std::cerr << "Reason: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << std::endl;
        }
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