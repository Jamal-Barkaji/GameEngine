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


class Renderer {
public:
    Renderer();
    ~Renderer();

    void RenderMesh(Transformer& transformer, Camera& camera, Shader& shader, std::vector<Mesh*> meshList);

    private:
    //TODO: Move textures and models to manager classes later
    Texture brickTexture;
    Texture concreteTexture;
    Model knightModel;
};
