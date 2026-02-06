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

    void renderScene(Scene& scene, Shader& shader, Camera& camera);
};