#pragma once

#include "Window.h"
#include "OpenGLRenderer.h"


class PhysicsSystem;

class Loop {
public:
    void run(Window& window, IOpenGLRenderer& renderer, Transformer& transformer, Camera& camera, Scene& scene, OpenGLShader& mainShader, OpenGLShader& shadowShader, PhysicsSystem& physics);

    GLfloat deltaTime = 0.0f;
    GLfloat lastTime = 0.0f;
};
