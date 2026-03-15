#pragma once

#include <string>
#include <glad/glad.h>
#include <iostream>

#include "ITexture.h"


class ResourceManager;

class OpenGLTexture : public ITexture {
public:
    OpenGLTexture();
    OpenGLTexture(std::string fileLoc);

    ~OpenGLTexture() override;

    void bindTexture() override;
    void unbindTexture();

private:
    bool loadTexture();
    bool loadTextureA();


    GLuint textureID;
    int width, height, bitDepth;

    std::string fileLocation;


    friend class ResourceManager;
};

