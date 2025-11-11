#include "Window.h"
#include "Renderer.h"
#include "Loop.h"
#include "Texture.h"


std::vector<Mesh*> meshList;

Texture brickTexture;

//TODO: Move this utility method out of main
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
                        unsigned int vertLength, unsigned int normalOffset) {

    for (size_t i = 0; i < indiceCount; i += 3) {
        unsigned int in0 = indices[i] * vertLength;
        unsigned int in1 = indices[i + 1] * vertLength;
        unsigned int in2 = indices[i + 2] * vertLength;
        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0] + 1,
                     vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0] + 1,
                     vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
        vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
        vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
        vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
    }

    for (size_t i = 0; i < verticeCount / vertLength; i ++) {
        unsigned int nOffset = i * vertLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
    }
}

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
    //   x       y     z         u      v           nx      ny      nz
        -1.0f, -1.0f, 0.0f,     0.0f,   0.0f,       0.0f,   0.0f,   0.0f,
        0.0f, -1.0f, 1.0f,      0.5f,   0.0f,       0.0f,   0.0f,   0.0f,
        1.0f, -1.0f, 0.0f,      1.0f,   0.0,        0.0f,   0.0f,   0.0f,
        0.0f,  1.0f, 0.0f,      0.5f,   1.0f,       0.0f,   0.0f,   0.0f
    };

    calcAverageNormals(indices, 12, vertices, 32, 8, 5);

    Mesh obj1;
    obj1.CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(&obj1);

    Mesh obj2;
    obj2.CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(&obj2);

    brickTexture = Texture("C:/Users/barka/CLionProjects/GameEngine/assets/textures/factory_brick_diff_4k.png");
    brickTexture.loadTexture();
    brickTexture.useTexture();

    Loop loop;
    loop.run(window, renderer, transformer, camera, shader, meshList);
    return 0;
}
