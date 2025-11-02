#include "Window.h"
#include "Renderer.h"
#include "Loop.h"
#include "Texture.h"


std::vector<Mesh*> meshList;

Texture brickTexture;

int main(int argc, char* argv[]) {
    Window window;
    Renderer renderer;
    Transformer transformer;
    Camera camera = Camera(window, glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 0.2f);

    Shader shader;

    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
    //   x       y     z         u      v
        -1.0f, -1.0f, 0.0f,     0.0f,   0.0f,
        0.0f, -1.0f, 1.0f,      0.5f,   0.0f,
        1.0f, -1.0f, 0.0f,      1.0f,   0.0,
        0.0f,  1.0f, 0.0f,      0.5f,   1.0f
    };

    Mesh obj1;
    obj1.CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(&obj1);

    Mesh obj2;
    obj2.CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(&obj2);

    brickTexture = Texture("C:/Users/barka/CLionProjects/GameEngine/assets/textures/factory_brick_diff_4k.png");
    brickTexture.loadTexture();
    brickTexture.useTexture();

    Loop loop;
    loop.run(window, renderer, transformer, camera, shader, meshList);
    return 0;
}
