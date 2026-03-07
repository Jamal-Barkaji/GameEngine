#include "GeometryGenerator.h"

#include "Mesh.h"
#include "Model.h"

#include <glm/vec3.hpp>
#include <glm/ext/quaternion_geometric.hpp>


void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
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

std::shared_ptr<Model> GeometryGenerator::generatePlane() {
    std::vector<unsigned int> planeIndices = {
        0, 2, 1,
        1, 2, 3
    };

    std::vector<float> planeVertices = {
        //   x       y     z         u      v           nx      ny      nz
        -10.0f, 0.0f, -10.0f,    0.0f,  0.0f,       0.0f,   1.0f,   0.0f,
        10.0f, 0.0f, -10.0f,     10.0f, 0.0f,       0.0f,   1.0f,   0.0f,
        -10.0f, 0.0f, 10.0f,     0.0f,  10.f,       0.0f,   1.0f,   0.0f,
        10.0f, 0.0f, 10.f,       10.f,  10.0f,      0.0f,   1.0f,   0.0f
    };

    std::shared_ptr<Mesh> planeMesh = std::make_shared<Mesh>();
    planeMesh->createMesh(planeVertices.data(), planeIndices.data(), 32, 6);

    AABB bounds = AABB::generateFromVertices(planeVertices, 8);
    planeMesh->setLocalBounds(bounds.min, bounds.max);

    std::shared_ptr<Model> planeModel = std::make_shared<Model>();
    planeModel->addMesh(planeMesh);

    return planeModel;
}


std::shared_ptr<Model> GeometryGenerator::generatePyramid() {
    std::vector<unsigned int> pyramidIndices = {
        0, 1, 3,
        1, 2, 3,
        2, 0, 3,
        0, 2, 1
    };

    std::vector<float> pyramidVertices = {
        //   x       y     z         u      v           nx      ny      nz
        -1.0f, -1.0f, -0.6f,    0.0f,   0.0f,       0.0f,   0.0f,   0.0f,
         0.0f, -1.0f,  1.0f,    0.5f,   0.0f,       0.0f,   0.0f,   0.0f,
         1.0f, -1.0f, -0.6f,    1.0f,   0.0f,       0.0f,   0.0f,   0.0f,
         0.0f,  1.0f,  0.0f,    0.5f,   1.0f,       0.0f,   0.0f,   0.0f
    };

    calcAverageNormals(pyramidIndices.data(), pyramidIndices.size(), pyramidVertices.data(), pyramidVertices.size(), 8, 5);

    std::shared_ptr<Mesh> pyramidMesh = std::make_shared<Mesh>();
    pyramidMesh->createMesh(pyramidVertices.data(), pyramidIndices.data(), pyramidVertices.size(), pyramidIndices.size());

    AABB bounds = AABB::generateFromVertices(pyramidVertices, 8);
    pyramidMesh->setLocalBounds(bounds.min, bounds.max);

    std::shared_ptr<Model> pyramidModel = std::make_shared<Model>();
    pyramidModel->addMesh(pyramidMesh);

    return pyramidModel;
}
