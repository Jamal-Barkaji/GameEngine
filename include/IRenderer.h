#pragma once

#include "Scene.h"


class IRenderer {
public:
    IRenderer() = default;

    virtual ~IRenderer() = default;

    virtual void renderFrame(Scene& scene, Camera& camera, Shader& mainShader, Shader& shadowShader) = 0;
};
