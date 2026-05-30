#pragma once
#include <memory>
#include <vector>


struct MeshData {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

class Model;

class GeometryGenerator {
public:
    static MeshData generatePlane();
    static MeshData generatePyramid();
    static MeshData generateCube();
};
