#pragma once

#include <glad/glad.h>

#include "PhysicsObject.h"


class Mesh {
    public:
        Mesh();
        ~Mesh();

        void createMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
        void drawMesh();
        void clearMesh();

        void setLocalBounds(const glm::vec3& minAABB, const glm::vec3& maxAABB);
        AABB getLocalBounds();

    private:
        GLuint VAO, VBO, IBO;
        GLsizei indexCount;

        AABB localBound;
};