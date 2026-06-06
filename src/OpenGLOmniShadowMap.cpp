#include "OpenGLOmniShadowMap.h"

#include <iostream>


OpenGLOmniShadowMap::OpenGLOmniShadowMap() : OpenGLShadowMap() {}
OpenGLOmniShadowMap::~OpenGLOmniShadowMap() {}

bool OpenGLOmniShadowMap::init(GLuint width, GLuint height) {
    shadowWidth = width; shadowHeight = height;

    glGenFramebuffers(1, &FBO);

    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);

    for (size_t i = 0; i < 6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0);

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

    return true;
}

void OpenGLOmniShadowMap::write() {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void OpenGLOmniShadowMap::read(GLenum textureUnit) {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);
}