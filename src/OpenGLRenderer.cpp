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
    shader.setMat4("projection", camera.getProjection());
    shader.setMat4("view", camera.calculateViewMatrix());
    shader.setVec3("eyePosition", camera.getCameraPosition());

    // Lights and Shadows
    if (!scene.directionalLight.empty()) {
        DirectionalLight* mainLight = &scene.directionalLight[0];

        mainLight->useLight(shader, "directionalLight");

        shader.setMat4("directionalLightTransform", mainLight->calculateLightTransform());

        // mainLight->getShadowMap()->read(GL_TEXTURE1);
        // shader.setInt("directionalShadowMap", 1);
    }
    if (!scene.pointLights.empty()) {
        int pointLightCount = static_cast<int>(scene.pointLights.size());
        shader.setInt("pointLightCount", pointLightCount);
        for (int i = 0; i < pointLightCount; i++) {
            std::string prefix = "pointLights[" + std::to_string(i) + "]";
            scene.pointLights[i].useLight(shader, prefix);
        }
    }

    if (!scene.spotLights.empty()) {
        int spotLightCount = static_cast<int>(scene.spotLights.size());
        shader.setInt("spotLightCount", spotLightCount);
        for (int i = 0; i < spotLightCount; i++) {
            std::string prefix = "spotLights[" + std::to_string(i) + "]";
            scene.spotLights[i].useLight(shader, prefix);
        }
    }

    for (const auto& entity : scene.entities) {
        // Set Model Matrix
        shader.setMat4("model", entity.transform);

        // Bind Material
        if (entity.renderData.material) {
            entity.renderData.material->bindMaterial(shader);
        }

        // Draw
        if (entity.renderData.model) {
            entity.renderData.model->renderModel(shader);
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
