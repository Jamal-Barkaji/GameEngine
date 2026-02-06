#pragma once
#include <memory>
#include <glm/glm.hpp>

class Model;
class Material;

struct RenderObject {
    std::shared_ptr<Model> model;
    std::shared_ptr<Material> material;
    glm::mat4 transform{1.0f};

    RenderObject() = default;
    RenderObject(std::shared_ptr<Model> m, std::shared_ptr<Material> mat, const glm::mat4& t)
        : model(m), material(mat), transform(t) {}
};
