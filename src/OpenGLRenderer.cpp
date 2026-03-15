#include "OpenGLRenderer.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValues.h"
#include "Material.h"
#include "Scene.h"


OpenGLRenderer::OpenGLRenderer() {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }

    glEnable(GL_DEPTH_TEST);
}

OpenGLRenderer::~OpenGLRenderer() {

}

void OpenGLRenderer::renderFrame(Scene& scene, Camera& camera, IShader& mainShader, IShader& shadowShader) {
    // if (!scene.directionalLight.empty()) {
    //     directionalShadowMapPass(scene, shadowShader);
    // }
    renderPass(scene, mainShader, camera);
}

void OpenGLRenderer::renderPass(Scene& scene, IShader& shader, Camera& camera) {
    //TODO: Make viewport dynamic based on window size
    glViewport(0, 0, 1366, 768);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     if (scene.skybox) {
         glm::mat4 skyView = camera.calculateViewMatrix();
         skyView = glm::mat4(glm::mat3(skyView));

         scene.skybox->drawSkybox(skyView, camera.getProjection());
     }

    shader.bindShader();

    // Global Frame Uniforms
    // glUniformMatrix4fv(shader.getProjectLocation(), 1, GL_FALSE, glm::value_ptr(camera.getProjection()));
    // glUniformMatrix4fv(shader.getViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
    // glUniform3f(shader.getEyePositionLocation(), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

    shader.setMat4("projection", camera.getProjection());
    shader.setMat4("view", camera.calculateViewMatrix());
    shader.setVec3("eyePosition", camera.getCameraPosition());

    // Lights and Shadows
    if (!scene.directionalLight.empty()) {
        DirectionalLight* mainLight = &scene.directionalLight[0];

        mainLight->useLight(shader);

        shader.setMat4("directionalLightTransform", mainLight->calculateLightTransform());

        // mainLight->getShadowMap()->read(GL_TEXTURE1);
        // shader.setInt("directionalShadowMap", 1);
    }
    // if (!scene.pointLights.empty()) {
    //     shader.setPointLights(scene.pointLights.data(), scene.pointLights.size());
    // }
    // if (!scene.spotLights.empty()) {
    //     shader.setSpotLights(scene.spotLights.data(), scene.spotLights.size());
    // }

    for (const auto& entity : scene.entities) {
        // 1. Set Model Matrix
        // glUniformMatrix4fv(shader.getModelLocation(), 1, GL_FALSE, glm::value_ptr(entity.transform));
        shader.setMat4("model", entity.transform);

        // 2. Bind Material
        entity.renderData.material->bindMaterial(shader);

        // 3. Draw
        if (entity.renderData.model) {
            entity.renderData.model->renderModel();
        }
    }

    glUseProgram(0);
}

void OpenGLRenderer::directionalShadowMapPass(Scene& scene, IShader& shadowShader) {
    // DirectionalLight* light = &scene.directionalLight[0];
    //
    // // Bind the specific framebuffer for shadows (off-screen rendering)
    // light->getShadowMap()->write();
    //
    // glEnable(GL_DEPTH_TEST);
    // glViewport(0, 0, light->getShadowMap()->getShadowWidth(), light->getShadowMap()->getShadowHeight());
    //
    // // Clear DEPTH only
    // glClear(GL_DEPTH_BUFFER_BIT);
    //
    // shadowShader.useShader();
    //
    // // Calculate Light Matrix (Ortho projection looking down the light dir)
    // glm::mat4 lightTransform = light->calculateLightTransform();
    // shadowShader.setDirectionalLightTransform(&lightTransform);
    //
    // // Render Scene Depth from Light's POV
    // for (const auto& obj : scene.entities) {
    //     glUniformMatrix4fv(shadowShader.getModelLocation(), 1, GL_FALSE, glm::value_ptr(obj.transform));
    //
    //     if (obj.renderData.model) {
    //         obj.renderData.model->renderModel();
    //     }
    // }
    //
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
