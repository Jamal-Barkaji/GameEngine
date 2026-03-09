#pragma once
#include <memory>
#include <vector>

#include "RenderObject.h"
#include "DirectionalLight.h"
#include "Entity.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "PhysicsObject.h"
#include "Skybox.h"


class Camera;

class Scene {
public:
    Scene();
    ~Scene();

    void clear();

    std::vector<RenderObject> renderObjects;
    std::vector<Entity> entities;
    std::shared_ptr<Skybox> skybox;

    Camera* activeCamera = nullptr;

    std::vector<DirectionalLight> directionalLight;
    std::vector<PointLight> pointLights;
    std::vector<SpotLight> spotLights;
};
