#pragma once

#include "ICubeMap.h"

#include <glad/glad.h>


class OpenGLCubeMap : public ICubeMap {
public:
    OpenGLCubeMap(unsigned int id);
    ~OpenGLCubeMap() override;

    void bind(unsigned int slot) override;
    void unbind() override;

private:
    unsigned int textureID;
};