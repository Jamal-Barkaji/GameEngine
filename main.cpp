#include <filesystem>

#include "Entity.h"
#include "GeometryGenerator.h"
#include "Window.h"
#include "OpenGLRenderer.h"
#include "Loop.h"
#include "Material.h"
#include "PhysicsSystem.h"
#include "Scene.h"
#include "Skybox.h"
#include "ResourceManager.h"


int main(int argc, char* argv[]) {
    Window window;
    OpenGLRenderer renderer;
    Transformer transformer;
    Camera camera = Camera(window, glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 0.2f);

    ResourceManager resourceManager;

    std::shared_ptr<OpenGLShader> mainShader = resourceManager.loadShader("Shaders/shader.vert", "Shaders/shader.frag");
    std::shared_ptr<OpenGLShader> directionalShadowShader = resourceManager.loadShader("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");

    Scene scene;

    Material brickMaterial = Material(1.0f, 32);
    Material concreteMaterial = Material(2.0f, 40);
    Material knightMaterial = Material(10.0f, 100);

    brickMaterial.albedoMap = resourceManager.loadTexture("Assets/Textures/factory_brick_diff_4k.png");
    concreteMaterial.albedoMap = resourceManager.loadTexture("Assets/Textures/painted_concrete_02_diff_4k.png");

    std::shared_ptr<Model> knightModel = resourceManager.loadModel("Assets/Models/SKM_DKM_Full.obj");

    Entity knightObject;
    knightObject.renderData.model = knightModel;
    knightObject.physicsData.localAABB = knightModel->getFullModelAABB();
    knightObject.renderData.material = std::make_shared<Material>(knightMaterial);
    knightObject.transform = glm::mat4(1.0f);
    knightObject.transform = glm::translate(knightObject.transform, glm::vec3(0.0f, 0.0f, 0.0f));
    knightObject.transform = glm::scale(knightObject.transform, glm::vec3(0.01f, 0.01f, 0.01f));
    scene.entities.push_back(knightObject);

    Entity pyramidObject;
    auto pyramidModel = GeometryGenerator::generatePyramid();
    pyramidObject.renderData.model = pyramidModel;
    pyramidObject.physicsData.localAABB = pyramidModel->getFullModelAABB();
    pyramidObject.renderData.material = std::make_shared<Material>(brickMaterial);
    pyramidObject.transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 4.0f));
    scene.entities.push_back(pyramidObject);

    Entity floorObject;
    floorObject.renderData.model = GeometryGenerator::generatePlane();
    floorObject.physicsData.localAABB = floorObject.renderData.model->getFullModelAABB();
    floorObject.renderData.material = std::make_shared<Material>(concreteMaterial);
    floorObject.transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    scene.entities.push_back(floorObject);

    DirectionalLight directionalMainLight = DirectionalLight(2048, 2048,
                                                            1.0f, 0.53f, 0.3f,
                                                            0.2f, 0.9f,
                                                            -10.0f, -12.0f, 18.0f);

    scene.directionalLight.push_back(directionalMainLight);

    PointLight p1 = PointLight(0.0f, 1.0f, 0.0f,
                                0.7f, 0.1f,
                                -4.0f, 0.0f, 0.0f,
                                0.2f, 0.2f, 0.1f);
    scene.pointLights.push_back(p1);

    PointLight p2 = PointLight(0.0f, 0.0f, 1.0f,
                                0.5f, 0.1f,
                                4.0f, 2.0f, 0.0f,
                                0.1f, 0.2f, 0.1f);
    scene.pointLights.push_back(p2);

    SpotLight s1 = SpotLight(1.0f, 1.0f, 1.0f,
                                0.2f, 1.0f,
                                0.0f, 3.0f, 4.0f,
                                1.0f, 0.0f, 0.0f,
                                0.0f, -1.0f, 0.0f,
                                20.0f);
    // glm::vec3 lowerLight = camera.getCameraPosition();
    // lowerLight.y -= 0.3f;
    // s1.setFlash(lowerLight, camera.getCameraDirection());
    scene.spotLights.push_back(s1);

    std::shared_ptr<OpenGLShader> skyboxShader = resourceManager.loadShader("Shaders/skybox.vert", "Shaders/skybox.frag");
    std::vector<std::string> skyboxFaces;
    skyboxFaces.push_back("Assets/Textures/Skyboxes/cupertin-lake_rt.tga");
    skyboxFaces.push_back("Assets/Textures/Skyboxes/cupertin-lake_lf.tga");
    skyboxFaces.push_back("Assets/Textures/Skyboxes/cupertin-lake_up.tga");
    skyboxFaces.push_back("Assets/Textures/Skyboxes/cupertin-lake_dn.tga");
    skyboxFaces.push_back("Assets/Textures/Skyboxes/cupertin-lake_bk.tga");
    skyboxFaces.push_back("Assets/Textures/Skyboxes/cupertin-lake_ft.tga");

    scene.skybox = std::make_shared<Skybox>(skyboxFaces, skyboxShader);

    PhysicsSystem physics;

    Loop loop;
    loop.run(window, renderer, transformer, camera, scene, *mainShader, *directionalShadowShader, physics);
    return 0;
}
