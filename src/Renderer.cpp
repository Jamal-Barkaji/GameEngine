#include "Renderer.h"

#include "Light.h"
#include "Material.h"


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

    // TODO: Encapsulate shader logic
    glm::mat4 model = transformer.getModelMatrix();
    glm::mat4 projection = camera.getProjection();
    glUniformMatrix4fv(shader.GetProjectLocation(), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(shader.GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

    glUniform3f(shader.getEyePositionLocation(), camera.getCameraPosition().x, camera.getCameraPosition().y,
                    camera.getCameraPosition().z);

    glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));


    // TODO: Encapsulate light logic
    Light mainLight = Light(1.0f, 1.0f, 1.0f, 0.2f,
                            2.0f, -1.0f, -2.0f, 0.3f);

    mainLight.useLight(shader.getAmbientIntensityLocation(), shader.getAmbientColourLocation(),
                        shader.getDiffuseIntesityLocation(), shader.getDirectionLocation(), shader.getSpecularIntensityLocation(), shader.getShininessLocation());

    Material shinyMaterial = Material(1.0f, 32);
    Material dullMaterial = Material(0.3f, 4);
    shinyMaterial.useMaterial(shader.getSpecularIntensityLocation(), shader.getShininessLocation());

        for (Mesh* mesh : meshList) {
            mesh->DrawMesh();
        }

    glUseProgram(0);
}
