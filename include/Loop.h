#pragma once

#include "Window.h"
#include "Renderer.h"


class PhysicsSystem;

class Loop {
public:
    void run(Window& window, IRenderer& renderer, Transformer& transformer, Camera& camera, Scene& scene, Shader& mainShader, Shader& shadowShader, PhysicsSystem& physics);

    GLfloat deltaTime = 0.0f;
    GLfloat lastTime = 0.0f;
};
