#pragma once

#include "PhysicsObject.h"


class IMesh {
public:
    virtual ~IMesh() = default;

    virtual void createMesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) = 0;
    virtual void drawMesh() = 0;
    virtual void clearMesh() = 0;

    virtual void setLocalBounds(const glm::vec3& minAABB, const glm::vec3& maxAABB) = 0;
    virtual AABB getLocalBounds() = 0;
};