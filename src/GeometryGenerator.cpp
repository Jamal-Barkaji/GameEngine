#include "GeometryGenerator.h"

#include <glm/vec3.hpp>
#include <glm/ext/quaternion_geometric.hpp>


void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, float* vertices, unsigned int verticeCount,
                        unsigned int vertLength, unsigned int normalOffset) {

    for (size_t i = 0; i < indiceCount; i += 3) {
        unsigned int in0 = indices[i] * vertLength;
        unsigned int in1 = indices[i + 1] * vertLength;
        unsigned int in2 = indices[i + 2] * vertLength;
        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0] + 1,
                     vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0] + 1,
                     vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
        vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
        vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
        vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
    }

    for (size_t i = 0; i < verticeCount / vertLength; i ++) {
        unsigned int nOffset = i * vertLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
    }
}

MeshData GeometryGenerator::generatePlane() {
    MeshData data;

    data.indices = {
        0, 2, 1,
        1, 2, 3
    };

    data.vertices = {
        //   x       y     z         u      v           nx      ny      nz
        -10.0f, 0.0f, -10.0f,    0.0f,  0.0f,       0.0f,   1.0f,   0.0f,
        10.0f, 0.0f, -10.0f,     10.0f, 0.0f,       0.0f,   1.0f,   0.0f,
        -10.0f, 0.0f, 10.0f,     0.0f,  10.f,       0.0f,   1.0f,   0.0f,
        10.0f, 0.0f, 10.f,       10.f,  10.0f,      0.0f,   1.0f,   0.0f
    };

    return data;
}


MeshData GeometryGenerator::generatePyramid() {
    MeshData data;

    data.indices = {
        0, 1, 3,
        1, 2, 3,
        2, 0, 3,
        0, 2, 1
    };

    data.vertices = {
        //   x       y     z         u      v           nx      ny      nz
        -1.0f, -1.0f, -0.6f,    0.0f,   0.0f,       0.0f,   0.0f,   0.0f,
         0.0f, -1.0f,  1.0f,    0.5f,   0.0f,       0.0f,   0.0f,   0.0f,
         1.0f, -1.0f, -0.6f,    1.0f,   0.0f,       0.0f,   0.0f,   0.0f,
         0.0f,  1.0f,  0.0f,    0.5f,   1.0f,       0.0f,   0.0f,   0.0f
    };

    calcAverageNormals(data.indices.data(), data.indices.size(), data.vertices.data(), data.vertices.size(), 8, 5);

    return data;
}

MeshData GeometryGenerator::generateCube() {
    MeshData data;

    data.indices = {
        // Front
        0, 1, 2,
        2, 1, 3,
        // Right
        2, 3, 5,
        5, 3, 7,
        // Back
        5, 7, 4,
        4, 7, 6,
        // Left
        4, 6, 0,
        0, 6, 1,
        // Top
        4, 0, 5,
        5, 0, 2,
        // Bottom
        1, 6, 3,
        3, 6, 7
    };

    data.vertices = {
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        -1.0f, 1.0f, 1.0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };

    return data;
}
