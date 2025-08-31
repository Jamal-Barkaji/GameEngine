#include "Window.h"
#include "Renderer.h"
#include "Loop.h"
#include <string>


std::vector<Mesh*> meshList;

int main(int argc, char* argv[]) {
    Window window;
    Renderer renderer;
    Transformer transformer;
    Camera camera = Camera(window);

    Shader shader;

    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    Mesh obj1;
    obj1.CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(&obj1);

    Mesh obj2;
    obj2.CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(&obj2);


    Loop loop;
    loop.run(window, renderer, transformer, camera, shader, meshList);
    return 0;
}
