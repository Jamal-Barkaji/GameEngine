#pragma once

#include <glad/glad.h>


class Mesh {
    public:
        Mesh();
        ~Mesh();

        void createMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
        void drawMesh();
        void clearMesh();

    private:
        GLuint VAO, VBO, IBO;
        GLsizei indexCount;
};