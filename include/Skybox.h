#pragma once

#include <memory>
#include <glm/glm.hpp>


class IMesh;
class IShader;
class ICubeMap;

class Skybox {
public:
    Skybox(std::shared_ptr<IMesh> mesh,
           std::shared_ptr<ICubeMap> texture,
           std::shared_ptr<IShader> shader);

    void drawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
    std::shared_ptr<IMesh> skyboxMesh;
    std::shared_ptr<ICubeMap> skyboxTexture;
    std::shared_ptr<IShader> skyboxShader;
};