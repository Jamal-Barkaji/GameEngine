#pragma once

#include "RenderObject.h"
#include "PhysicsObject.h"


struct Entity {
    glm::mat4 transform{};
    RenderObject renderData;
    PhysicsObject physicsData;
};
