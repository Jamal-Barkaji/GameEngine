#pragma once

#include <string>
#include <glad/glad.h>
#include <iostream>


class Texture {
    public:
    Texture();
    Texture(std::string fileLoc);

    bool loadTexture();
    bool loadTextureA();

    void useTexture();
    void clearTexture();

    ~Texture();

    

    private:
    GLuint textureID;
    int width, height, bitDepth;

    std::string fileLocation;
};

