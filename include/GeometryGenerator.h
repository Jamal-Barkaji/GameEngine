#pragma once
#include <memory>


class Model;

class GeometryGenerator {
public:
    static std::shared_ptr<Model> generatePlane();
    static std::shared_ptr<Model> generatePyramid();
};
