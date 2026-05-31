#pragma once

#include <glad/glad.h>

#include "BaseMesh.h"
#include "PhysicsObject.h"


class OpenGLMesh : public BaseMesh {
    public:
        OpenGLMesh();
        ~OpenGLMesh() override;

        void initMesh(const float* vertices, const unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) override;
        void drawMesh() override;
        void clearMesh() override;

    private:
        GLuint VAO, VBO, IBO;
        GLsizei indexCount;
};