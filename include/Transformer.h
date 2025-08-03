#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Transformer {
public:
    void transform();
    glm::mat4 getModelMatrix() const;

private:
    bool direction = true;
    float triOffSet = 0.0f;
    float triMaxOffSet = 0.7f;
    float triIncrement = 0.05;
    const float toRadians = 3.14159265f / 180.0f;
    float currAngle = 0.0f;
    bool sizeDirection = true;
    float currSize = 0.4f;
    float maxSize = 0.8f;
    float minSize = 0.1f;
};
