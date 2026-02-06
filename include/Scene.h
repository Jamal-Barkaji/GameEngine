#pragma once
#include <memory>
#include <vector>

#include "RenderObject.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Camera;

class Scene {
public:
    Scene();
    ~Scene();

    void clear();

    std::vector<RenderObject> renderObjects;

    Camera* activeCamera = nullptr;

    std::vector<DirectionalLight> directionalLight;
    std::vector<PointLight> pointLights;
    std::vector<SpotLight> spotLights;
};
