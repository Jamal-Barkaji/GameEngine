#include "Scene.h"


Scene::Scene() = default;

Scene::~Scene() {
    clear();
}

void Scene::clear() {
    renderObjects.clear();
    directionalLight.clear();
    pointLights.clear();
    spotLights.clear();
    activeCamera = nullptr;
}
