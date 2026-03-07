#pragma once

#include <glm/glm.hpp>
#include <vector>


struct AABB {
    glm::vec3 min;
    glm::vec3 max;

    static AABB generateFromVertices(const std::vector<float>& vertexData, int stride = 8) {
        glm::vec3 minAABB = glm::vec3(FLT_MAX);
        glm::vec3 maxAABB = glm::vec3(-FLT_MAX);

        // Loop through the flat float array, jumping by the stride (e.g., 8 floats per vertex)
        for (size_t i = 0; i < vertexData.size(); i += stride) {
            glm::vec3 pos(vertexData[i], vertexData[i+1], vertexData[i+2]);

            minAABB = glm::min(minAABB, pos);
            maxAABB = glm::max(maxAABB, pos);
        }
        return {minAABB, maxAABB};
    }
};

struct PhysicsObject {
    AABB worldAABB{};
    AABB localAABB{};
    bool active = true;
};
