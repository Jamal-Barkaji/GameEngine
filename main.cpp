#include <filesystem>

#include "Entity.h"
#include "GeometryGenerator.h"
#include "Window.h"
#include "OpenGLRenderer.h"
#include "Loop.h"
#include "Material.h"
#include "OpenGLResourceFactory.h"
#include "PhysicsSystem.h"
#include "Scene.h"
#include "Skybox.h"
#include "ResourceManager.h"


std::shared_ptr<Model> createModelFromData(const MeshData& data, int vertexStride = 8) {
    auto mesh = std::make_shared<OpenGLMesh>();
    mesh->initMesh(data.vertices.data(), data.indices.data(), data.vertices.size(), data.indices.size());

    AABB bounds = AABB::generateFromVertices(data.vertices, vertexStride);
    mesh->setLocalBounds(bounds.min, bounds.max);

    auto model = std::make_shared<Model>();
    model->addMesh(mesh);

    return model;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    OpenGLRenderer::configureContext();
    Window window;
    window.init(SDL_WINDOW_OPENGL);
    OpenGLRenderer renderer(window.getSDLWindow());

    Transformer transformer;
    Camera camera = Camera(window, glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 0.2f);

    std::unique_ptr<OpenGLResourceFactory> resourceFactory;
    ResourceManager resourceManager(std::make_unique<OpenGLResourceFactory>());

    std::shared_ptr<IShader> mainShader = resourceManager.loadShader("Shaders/shader.vert", "Shaders/shader.frag");
    std::shared_ptr<IShader> directionalShadowShader = resourceManager.loadShader("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");

    Scene scene;

    //TODO: Materials shouldn't need manually set values. They should be loaded from the model file or set to some default. Also add PBR support
    Material brickMaterial = Material(1.0f, 32);
    Material concreteMaterial = Material(2.0f, 40);
    Material knightMaterial = Material();

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
    auto pyramidModel = createModelFromData(GeometryGenerator::generatePyramid());
    pyramidObject.renderData.model = pyramidModel;
    pyramidObject.physicsData.localAABB = pyramidModel->getFullModelAABB();
    pyramidObject.renderData.material = std::make_shared<Material>(brickMaterial);
    pyramidObject.transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 4.0f));
    scene.entities.push_back(pyramidObject);

    Entity floorObject;
    auto floorModel = createModelFromData(GeometryGenerator::generatePlane());
    floorObject.renderData.model = floorModel;
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

    // 1. Load Shader
    std::shared_ptr<IShader> skyboxShader = resourceManager.loadShader("Shaders/skybox.vert", "Shaders/skybox.frag");

    // 2. Load Texture
    std::vector<std::string> skyboxFaces = {
        "Assets/Textures/Skyboxes/cupertin-lake_rt.tga",
        "Assets/Textures/Skyboxes/cupertin-lake_lf.tga",
        "Assets/Textures/Skyboxes/cupertin-lake_up.tga",
        "Assets/Textures/Skyboxes/cupertin-lake_dn.tga",
        "Assets/Textures/Skyboxes/cupertin-lake_bk.tga",
        "Assets/Textures/Skyboxes/cupertin-lake_ft.tga"
    };
    auto skyboxTexture = resourceManager.loadCubeMap(skyboxFaces);

    MeshData cubeData = GeometryGenerator::generateCube();
    auto skyboxMesh = resourceManager.requestMeshContainer();
    skyboxMesh->initMesh(cubeData.vertices.data(), cubeData.indices.data(),
                           cubeData.vertices.size(), cubeData.indices.size());

    scene.skybox = std::make_shared<Skybox>(skyboxMesh, skyboxTexture, skyboxShader);

    PhysicsSystem physics;

    Loop loop;
    loop.run(window, renderer, transformer, camera, scene, *mainShader, *directionalShadowShader, physics);
    return 0;
}
