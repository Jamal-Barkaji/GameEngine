#include "Renderer.h"


Renderer::Renderer() {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }

    glEnable(GL_DEPTH_TEST);

   // CreateObjects();

}

Renderer::~Renderer() {

}


void Renderer::RenderMesh(Transformer& transformer, Camera& camera, Shader& shader, std::vector<Mesh*> meshList) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.UseShader();


    glm::mat4 model = transformer.getModelMatrix();
    glm::mat4 projection = camera.getProjection();
    glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(shader.GetProjectLocation(), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(shader.GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

        for (Mesh* mesh : meshList) {
            mesh->DrawMesh();
        }

    glUseProgram(0);
}
