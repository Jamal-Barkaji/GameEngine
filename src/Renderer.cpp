#include "Renderer.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValues.h"
#include "Material.h"
#include "Scene.h"


Renderer::Renderer() {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }

    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer() {

}

void Renderer::renderFrame(Scene& scene, Camera& camera, Shader& mainShader, Shader& shadowShader) {
    if (!scene.directionalLight.empty()) {
        directionalShadowMapPass(scene, shadowShader);
    }
    renderPass(scene, mainShader, camera);
}

void Renderer::renderPass(Scene& scene, Shader& shader, Camera& camera) {
    //TODO: Make viewport dynamic based on window size
    glViewport(0, 0, 1366, 768);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.UseShader();

    // Global Frame Uniforms
    glUniformMatrix4fv(shader.GetProjectLocation(), 1, GL_FALSE, glm::value_ptr(camera.getProjection()));
    glUniformMatrix4fv(shader.GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
    glUniform3f(shader.getEyePositionLocation(), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

    // Lights and Shadows
    if (!scene.directionalLight.empty()) {
        DirectionalLight* mainLight = &scene.directionalLight[0];
        shader.setDirectionalLight(mainLight);

        glm::mat4 lightTransform = mainLight->calculateLightTransform();
        shader.setDirectionalLightTransform(&lightTransform);

        mainLight->getShadowMap()->read(GL_TEXTURE1);
        shader.setDirectionalShadowMap(1);
    }
    if (!scene.pointLights.empty()) {
        shader.setPointLights(scene.pointLights.data(), scene.pointLights.size());
    }
    if (!scene.spotLights.empty()) {
        shader.setSpotLights(scene.spotLights.data(), scene.spotLights.size());
    }

    for (const auto& obj : scene.renderObjects) {
        // 1. Set Model Matrix
        glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE, glm::value_ptr(obj.transform));

        // 2. Bind Material
        obj.material->bind(shader);

        // 3. Draw
        if (obj.model) {
            obj.model->renderModel();
        }
    }

    glUseProgram(0);
}

void Renderer::directionalShadowMapPass(Scene& scene, Shader& shadowShader) {
    DirectionalLight* light = &scene.directionalLight[0];

    // Bind the specific framebuffer for shadows (off-screen rendering)
    light->getShadowMap()->write();

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, light->getShadowMap()->getShadowWidth(), light->getShadowMap()->getShadowHeight());

    // Clear DEPTH only
    glClear(GL_DEPTH_BUFFER_BIT);

    shadowShader.UseShader();

    // Calculate Light Matrix (Ortho projection looking down the light dir)
    glm::mat4 lightTransform = light->calculateLightTransform();
    shadowShader.setDirectionalLightTransform(&lightTransform);

    // Render Scene Depth from Light's POV
    for (const auto& obj : scene.renderObjects) {
        glUniformMatrix4fv(shadowShader.GetModelLocation(), 1, GL_FALSE, glm::value_ptr(obj.transform));

        if (obj.model) {
            obj.model->renderModel();
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
