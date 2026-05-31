#include "Skybox.h"
#include "IMesh.h"
#include "IShader.h"
#include "ICubeMap.h"


Skybox::Skybox(std::shared_ptr<IMesh> mesh,
               std::shared_ptr<ICubeMap> texture,
               std::shared_ptr<IShader> shader)
    : skyboxMesh(mesh), skyboxTexture(texture), skyboxShader(shader) {
}

void Skybox::drawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    if (!skyboxMesh || !skyboxTexture || !skyboxShader) return;

    viewMatrix = glm::mat4(glm::mat3(viewMatrix));

    skyboxShader->bindShader();
    skyboxShader->setMat4("projection", projectionMatrix);
    skyboxShader->setMat4("view", viewMatrix);

    skyboxTexture->bind();
    skyboxMesh->drawMesh();
    skyboxTexture->unbind();
}