#include "OpenGLCubeMap.h"


OpenGLCubeMap::OpenGLCubeMap(unsigned int id) : textureID(id) {}
OpenGLCubeMap::~OpenGLCubeMap() { glDeleteTextures(1, &textureID); }

void OpenGLCubeMap::bind(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}

void OpenGLCubeMap::unbind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}