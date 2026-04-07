#include "BaseMesh.h"


void BaseMesh::setLocalBounds(const glm::vec3& minAABB, const glm::vec3& maxAABB) {
    localBound = { minAABB, maxAABB };
}

AABB BaseMesh::getLocalBounds() {
    return localBound;
}
