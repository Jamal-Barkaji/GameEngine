#include "Renderer.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValues.h"
#include "Material.h"


Renderer::Renderer() {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }

    //TODO: Move this texture logic somewhere more appropriate
    brickTexture = Texture("C:/Users/barka/CLionProjects/GameEngine/assets/textures/factory_brick_diff_4k.png");
    brickTexture.loadTexture();
    concreteTexture = Texture("C:/Users/barka/CLionProjects/GameEngine/assets/textures/painted_concrete_02_diff_4k.png");
    concreteTexture.loadTexture();

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
    DirectionalLight directionalMainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
                                                    0.1f, 0.3f,
                                                       0.0f, 0.0f, -1.0f);



    PointLight pointLights[MAX_POINT_LIGHTS];
    SpotLight spotLights[MAX_SPOT_LIGHTS];

    unsigned int pointLightCount = 0;
    pointLights[0] = PointLight(0.0f, 1.0f, 0.0f,
                                0.7f, 0.1f,
                                -4.0f, 0.0f, 0.0f,
                                0.3f, 0.2f, 0.1f);
    pointLightCount++;

    pointLights[1] = PointLight(0.0f, 0.0f, 1.0f,
                                0.5f, 0.1f,
                                4.0f, 2.0f, 0.0f,
                                0.3f, 0.1f, 0.1f);
    pointLightCount++;

    unsigned int spotLightCount = 0;
    spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
                                0.2f, 1.0f,
                                0.0f, 3.0f, 4.0f,
                                1.0f, 0.0f, 0.0f,
                                0.0f, -1.0f, 0.0f,
                                20.0f);
    spotLightCount++;

    shader.setDirectionalLight(&directionalMainLight);
    shader.setPointLights(pointLights, pointLightCount);
    shader.setSpotLights(spotLights, spotLightCount);

    //TODO: Remember to move this
    brickTexture.useTexture();

    // TODO: Encapsulate material logic
    Material shinyMaterial = Material(3.0f, 100);
    Material dullMaterial = Material(0.5f, 10);
    dullMaterial.useMaterial(shader.getSpecularIntensityLocation(), shader.getShininessLocation());


    // TODO: Encapsulate logic for cycling through multiple models
    for (size_t i = 0; i < meshList.size(); i++) {

        // Floor
        if (i == 2) {
            concreteTexture.useTexture();
            shinyMaterial.useMaterial(shader.getSpecularIntensityLocation(), shader.getShininessLocation());
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, -1.0f, -2.5f));
            model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
        }

        glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
        meshList[i]->DrawMesh();
    }

    glUseProgram(0);
}
