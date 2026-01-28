#pragma once

#include <string>
#include <glad/glad.h>
#include <iostream>


class ResourceManager;

class Texture {
public:
    Texture();
    Texture(std::string fileLoc);

    ~Texture();

    void useTexture();
    void clearTexture();

private:
    bool loadTexture();
    bool loadTextureA();


    GLuint textureID;
    int width, height, bitDepth;

    std::string fileLocation;


    friend class ResourceManager;
};

