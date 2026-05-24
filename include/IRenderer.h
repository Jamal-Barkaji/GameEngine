#pragma once

#include "Scene.h"


class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void swapBuffers() = 0;

    virtual void renderFrame(Scene& scene, Camera& camera, IShader& mainShader, IShader& shadowShader) = 0;
};
