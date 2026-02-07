#include "GeometryGenerator.h"
#include "Window.h"
#include "Renderer.h"
#include "Loop.h"
#include "Texture.h"
#include "Material.h"
#include "Scene.h"


// //TODO: Move this utility method out of main
// void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
//                         unsigned int vertLength, unsigned int normalOffset) {
//
//     for (size_t i = 0; i < indiceCount; i += 3) {
//         unsigned int in0 = indices[i] * vertLength;
//         unsigned int in1 = indices[i + 1] * vertLength;
//         unsigned int in2 = indices[i + 2] * vertLength;
//         glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0] + 1,
//                      vertices[in1 + 2] - vertices[in0 + 2]);
//         glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0] + 1,
//                      vertices[in2 + 2] - vertices[in0 + 2]);
//         glm::vec3 normal = glm::cross(v1, v2);
//         normal = glm::normalize(normal);
//
//         in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
//         vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
//         vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
//         vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
//     }
//
//     for (size_t i = 0; i < verticeCount / vertLength; i ++) {
//         unsigned int nOffset = i * vertLength + normalOffset;
//         glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
//         vec = glm::normalize(vec);
//         vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
//     }
// }

int main(int argc, char* argv[]) {
    Window window;
    Renderer renderer;
    Transformer transformer;
    Camera camera = Camera(window, glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 0.2f);

    Shader shader;

    ResourceManager resourceManager;

    Scene scene;

    Material brickMaterial = Material(1.0f, 32);
    Material concreteMaterial = Material(2.0f, 40);
    Material knightMaterial = Material(10.0f, 100);

    std::shared_ptr<Model> knightModel = resourceManager.loadModel("C:/Users/barka/CLionProjects/GameEngine/Assets/Models/SKM_DKM_Full.obj");

    brickMaterial.albedoMap = resourceManager.loadTexture("C:/Users/barka/CLionProjects/GameEngine/Assets/Textures/factory_brick_diff_4k.png");
    concreteMaterial.albedoMap = resourceManager.loadTexture("C:/Users/barka/CLionProjects/GameEngine/Assets/Textures/painted_concrete_02_diff_4k.png");

    RenderObject knightObject;
    knightObject.model = knightModel;
    knightObject.material = std::make_shared<Material>(knightMaterial);
    knightObject.transform = glm::translate(knightObject.transform, glm::vec3(0.0f, 0.0f, 0.0f));
    knightObject.transform = glm::scale(knightObject.transform, glm::vec3(0.01f, 0.01f, 0.01f));
    scene.renderObjects.push_back(knightObject);

    RenderObject pyramidObject;
    pyramidObject.model = GeometryGenerator::generatePyramid();
    pyramidObject.material = std::make_shared<Material>(brickMaterial);
    pyramidObject.transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 4.0f));
    scene.renderObjects.push_back(pyramidObject);

    RenderObject floorObject;
    floorObject.model = GeometryGenerator::generatePlane();
    floorObject.material = std::make_shared<Material>(concreteMaterial);
    floorObject.transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    scene.renderObjects.push_back(floorObject);

    // DirectionalLight directionalMainLight = DirectionalLight(1024, 1024,
    //                                                         1.0f, 1.0f, 1.0f,
    //                                                         0.1f, 0.3f,
    //                                                         0.0f, 0.0f, -1.0f);
    //
    // scene.directionalLight.push_back(directionalMainLight);

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

    Loop loop;
    loop.run(window, renderer, transformer, camera, scene, shader);
    return 0;
}
