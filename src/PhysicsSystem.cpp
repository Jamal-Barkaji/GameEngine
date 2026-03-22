#include "PhysicsSystem.h"
#include "Entity.h"


PhysicsSystem::PhysicsSystem() = default;

PhysicsSystem::~PhysicsSystem() = default;


bool PhysicsSystem::checkCollision(const AABB& box1, const AABB& box2) {
    bool collisionX = box1.max.x >= box2.min.x && box2.max.x >= box1.min.x;
    bool collisionY = box1.max.y >= box2.min.y && box2.max.y >= box1.min.y;
    bool collisionZ = box1.max.z >= box2.min.z && box2.max.z >= box1.min.z;

    return collisionX && collisionY && collisionZ;
}

void PhysicsSystem::updateWorldAABB(Entity& entity) {
    glm::vec3 position = glm::vec3(entity.transform[3]);
    float scaleX = glm::length(glm::vec3(entity.transform[0]));

    entity.physicsData.worldAABB.min = (entity.physicsData.localAABB.min * scaleX) + position;
    entity.physicsData.worldAABB.max = (entity.physicsData.localAABB.max * scaleX) + position;
}

void PhysicsSystem::step(Camera& camera, std::vector<Entity>& entities, float deltaTime) {
    AABB camBox = camera.getAABB();

    for (auto& entity : entities) {
        if (!entity.physicsData.active) continue;

        updateWorldAABB(entity);

        // Check against camera
        if (checkCollision(camBox, entity.physicsData.worldAABB)) {
            camera.moveCameraBackwards(deltaTime);
        }
    }
}
