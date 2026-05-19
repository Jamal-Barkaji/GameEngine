#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include "glm/gtc/type_ptr.hpp"

#include "OpenGLTexture.h"
#include "OpenGLMesh.h"
#include "OpenGLShader.h"


class Skybox {
public:
    Skybox();
    Skybox(std::vector<std::string> faceLocations, std::shared_ptr<OpenGLShader> shader);

    ~Skybox();

    void drawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

    unsigned int getProjectionMatrix();
    unsigned int getViewMatrix();

private:
    std::unique_ptr<OpenGLMesh> skyboxMesh;
    std::shared_ptr<OpenGLShader> skyboxShader;

    unsigned int skyboxTextureID;
    unsigned int uniformProjection, uniformView;
};