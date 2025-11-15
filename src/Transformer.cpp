#include "Transformer.h"


void Transformer::transform() {
    if (direction) {
        triOffSet += triIncrement;
    }
    else {
        triOffSet -= triIncrement;
    }

    if (abs(triOffSet) >= triMaxOffSet) {
        direction = !direction;
    }

    currAngle += 0.5f;
    if (currAngle >= 360.0f) {
        currAngle -= 360.0f;
    }
/**
    if (sizeDirection) {
        currSize += 0.001f;
    }
    else {
        currSize -= 0.001f;
    }

    if (currSize >= maxSize || currSize <= minSize) {
        sizeDirection = !sizeDirection;
    }
    **/
}

glm::mat4 Transformer::getModelMatrix() const {
    glm::mat4 model(1.0f);

    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    //model = glm::rotate(model, currAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    //model = glm::scale(model, glm::vec3(currSize, currSize, 1.0f));
    

    return model;
}
