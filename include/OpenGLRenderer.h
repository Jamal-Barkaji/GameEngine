#pragma once

#include <glad/glad.h>
#include <iostream>
#include <vector>

#include "Transformer.h"
#include "Camera.h"
#include "OpenGLMesh.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "Model.h"
#include "DirectionalLight.h"
#include "IRenderer.h"
#include "Material.h"
#include "ResourceManager.h"


class Scene;

class OpenGLRenderer : public IRenderer {
public:
    OpenGLRenderer(SDL_Window* window);
    ~OpenGLRenderer() override;

    static void configureContext();

    void swapBuffers() override;

    void renderFrame(Scene& scene, Camera& camera, IShader& mainShader, IShader& shadowShader) override;

private:
    void directionalShadowMapPass(Scene& scene, IShader& shadowShader);
    void renderPass(Scene& scene, IShader& mainShader, Camera& camera);

    SDL_Window* window;
    SDL_GLContext glContext;
};