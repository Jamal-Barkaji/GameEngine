#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <glad/glad.h>

#include "stb_image.h"


class Texture {
    public:
    Texture();
    Texture(std::string fileLoc);

    void loadTexture();
    void useTexture();
    void clearTexture();

    ~Texture();

    

    private:
    GLuint textureID;
    int width, height, bitDepth;

    std::string fileLocation;
};

