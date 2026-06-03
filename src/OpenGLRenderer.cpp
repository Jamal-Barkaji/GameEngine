#include "OpenGLRenderer.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValues.h"
#include "Material.h"
#include "Scene.h"


OpenGLRenderer::OpenGLRenderer(SDL_Window* window) : window(window) {
    // Context Creation
    glContext = SDL_GL_CreateContext(window);

    if (!glContext) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << '\n';
        return;
    }

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }

    glEnable(GL_DEPTH_TEST);
}

OpenGLRenderer::~OpenGLRenderer() {
    SDL_GL_DeleteContext(glContext);
}


void OpenGLRenderer::configureContext() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
}

void OpenGLRenderer::swapBuffers() {
    SDL_GL_SwapWindow(window);
}

void OpenGLRenderer::renderFrame(Scene& scene, Camera& camera, IShader& mainShader, IShader& shadowShader) {
    // Setup default viewport for the window
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    if (!scene.directionalLight.empty()) {
        directionalShadowMapPass(scene, shadowShader);
    }
    renderPass(scene, mainShader, camera);

    swapBuffers();
}

void OpenGLRenderer::renderPass(Scene& scene, IShader& shader, Camera& camera) {
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     if (scene.skybox) {
         glm::mat4 skyView = camera.calculateViewMatrix();
         skyView = glm::mat4(glm::mat3(skyView));

         glDepthMask(GL_FALSE);
         scene.skybox->drawSkybox(skyView, camera.getProjection());
         glDepthMask(GL_TRUE);
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

        mainLight->getShadowMap()->read(GL_TEXTURE1);
        shader.setInt("directionalShadowMap", 1);
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
    DirectionalLight* light = &scene.directionalLight[0];

    // Save current OpenGL state
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    light->getShadowMap()->write();

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.25f, 4.0f);

    glViewport(0, 0, light->getShadowMap()->getShadowWidth(), light->getShadowMap()->getShadowHeight());

    glClearDepth(1.0f);
    glClear(GL_DEPTH_BUFFER_BIT);

    shadowShader.bindShader();

    glm::mat4 lightTransform = light->calculateLightTransform();
    shadowShader.setMat4("directionalLightTransform", lightTransform);

    for (const auto& obj : scene.entities) {
        shadowShader.setMat4("model", obj.transform);

        if (obj.renderData.model) {
            obj.renderData.model->renderModel(shadowShader);
        }
    }

    glDisable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(0.0f, 0.0f);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);
    glReadBuffer(GL_BACK);

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
    glUseProgram(0);
}
