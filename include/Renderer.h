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


class Renderer {
public:
    Renderer();
    ~Renderer();

    void RenderMesh(Transformer& transformer, Camera& camera, Shader& shader, std::vector<Mesh*> meshList);

    private:
    //TODO: Move textures and models to manager classes later
    ResourceManager resources;

    Material brickMaterial = Material(1.0f, 32);
    std::shared_ptr<Texture> brickTexture;
    Material concreteMaterial = Material(0.5f, 10);
    std::shared_ptr<Texture> concreteTexture;

    Material knightMaterial = Material(10.0f, 100);
    std::shared_ptr<Model> knightModel;
};