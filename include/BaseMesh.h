#pragma once
#include "IMesh.h"


class BaseMesh : public IMesh {
public:
    virtual ~BaseMesh() = default;

    void setLocalBounds(const glm::vec3& minAABB, const glm::vec3& maxAABB) override;
    AABB getLocalBounds() override;

    virtual void createMesh(const float* vertices, const unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) = 0;
    virtual void drawMesh() = 0;
    virtual void clearMesh() = 0;

protected:
    AABB localBound{};
};
