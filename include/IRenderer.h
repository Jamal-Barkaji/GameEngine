#pragma once

#include "Scene.h"


class IOpenGLRenderer {
public:
    virtual ~IOpenGLRenderer() = default;

    virtual void renderFrame(Scene& scene, Camera& camera, IShader& mainShader, IShader& shadowShader) = 0;
};
