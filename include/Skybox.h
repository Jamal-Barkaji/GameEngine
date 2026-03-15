#pragma once

#include <vector>
#include <string>

#include <glad\glad.h>
#include <glm\glm.hpp>
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

    GLuint getProjectionMatrix();
    GLuint getViewMatrix();

private:
    std::unique_ptr<OpenGLMesh> skyboxMesh;
    std::shared_ptr<OpenGLShader> skyboxShader;

    GLuint skyboxTextureID;
    GLuint uniformProjection, uniformView;
};