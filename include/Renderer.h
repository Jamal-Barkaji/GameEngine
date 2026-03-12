#pragma once

#include <glad/glad.h>
#include <iostream>
#include <vector>

#include "Transformer.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "DirectionalLight.h"
#include "IRenderer.h"
#include "Material.h"
#include "ResourceManager.h"


class Scene;

class Renderer : public IRenderer {
public:
    Renderer();
    ~Renderer() override;

    void renderFrame(Scene& scene, Camera& camera, Shader& mainShader, Shader& shadowShader) override;

private:
    void directionalShadowMapPass(Scene& scene, Shader& shadowShader);
    void renderPass(Scene& scene, Shader& mainShader, Camera& camera);
};