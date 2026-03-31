#pragma once

#include <glad/glad.h>

#include "IMesh.h"
#include "PhysicsObject.h"


class OpenGLMesh : public IMesh {
    public:
        OpenGLMesh();
        ~OpenGLMesh() override;

        void createMesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) override;
        void drawMesh() override;
        void clearMesh() override;

        void setLocalBounds(const glm::vec3& minAABB, const glm::vec3& maxAABB) override;
        AABB getLocalBounds() override;

    private:
        GLuint VAO, VBO, IBO;
        GLsizei indexCount;

        AABB localBound{};
};