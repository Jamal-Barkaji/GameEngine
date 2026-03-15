#pragma once


class IMesh {
public:
    virtual ~IMesh() = default;

    virtual void createMesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) = 0;
    virtual void clearMesh() = 0;

    virtual void drawMesh() = 0;
};