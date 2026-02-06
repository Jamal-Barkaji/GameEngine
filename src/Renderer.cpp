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

// void directionalShadowMapPass(DirectionalLight* light) {
//     Shader directionalShadowShader = Shader();
//     directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");
//
//     directionalShadowShader.UseShader();
//     glViewport(0, 0, light->getShadowMap()->getShadowWidth(), light->getShadowMap()->getShadowHeight());
//
//     light->getShadowMap()->write();
//     glClear(GL_DEPTH_BUFFER_BIT);
//
//     uniformModel = directionalShadowShader.GetModelLocation();
//     directionalShadowShader.setDirectionalLightTransform(&light->calculateLightTransform());
//
//     // Render scene from light's point of view
//
//     glBindFramebuffer(GL_FRAMEBUFFER, 0);
//     }

//
// void renderPass(glm::mat4 projectionMatrix, glm::mat3 viewMatrix) {
//     // This should probably have something similar to what is currently in RenderMesh() directly
// }


void Renderer::renderScene(Scene& scene, Shader& shader, Camera& camera) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.UseShader();

    // Global Frame Uniforms
    glUniformMatrix4fv(shader.GetProjectLocation(), 1, GL_FALSE, glm::value_ptr(camera.getProjection()));
    glUniformMatrix4fv(shader.GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
    glUniform3f(shader.getEyePositionLocation(), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

    // Set Lights from Scene
    if (!scene.directionalLight.empty()) {
        shader.setDirectionalLight(&scene.directionalLight[0]);
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
