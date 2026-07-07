#pragma once

#include "Window.h"
#include "OpenGLRenderer.h"


class PhysicsSystem;

class Loop {
public:
    void run(Window& window, IRenderer& renderer, Transformer& transformer, Camera& camera, Scene& scene, IShader& mainShader, IShader& directionalShadowShader, IShader& omniShadowShader, PhysicsSystem& physics);

    float deltaTime = 0.0f;
    float lastTime = 0.0f;
};
