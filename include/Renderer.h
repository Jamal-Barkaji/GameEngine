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
#include "Material.h"
#include "ResourceManager.h"


class Scene;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void renderFrame(Scene& scene, Camera& camera, Shader& mainShader, Shader& shadowShader);

private:
    void directionalShadowMapPass(Scene& scene, Shader& shadowShader);
    void renderPass(Scene& scene, Shader& mainShader, Camera& camera);
};