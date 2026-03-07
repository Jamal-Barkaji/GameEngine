#pragma once

#include <vector>

#include "Camera.h"
#include "PhysicsObject.h"


struct Entity;

class PhysicsSystem {
public:
    PhysicsSystem();
    ~PhysicsSystem();

    bool checkCollision(const AABB& box1, const AABB& box2);
    void updateWorldAABB(Entity& entity);
    void step(Camera& camera, std::vector<Entity>& entities, float deltaTime);

private:

};
