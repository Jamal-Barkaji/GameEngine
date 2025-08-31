#pragma once

#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "Transformer.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"


class Renderer {
public:
    Renderer();
    ~Renderer();

    void RenderMesh(Transformer& transformer, Camera& camera, Shader& shader, std::vector<Mesh*> meshList);

    private:

};
