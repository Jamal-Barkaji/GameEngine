#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "IResourceFactory.h"


class ITexture;
class OpenGLTexture;
class OpenGLShader;
class Model;

class ResourceManager {
public:
    ResourceManager(std::unique_ptr<IResourceFactory> factory);


    std::shared_ptr<IMesh> createMesh();

    std::shared_ptr<ITexture> loadTexture(const std::string& path);
    std::shared_ptr<ITexture> getDebugTexture();

    std::shared_ptr<OpenGLShader> loadShader(const std::string& vert, const std::string& frag);

    std::shared_ptr<Model> loadModel(const std::string& path);

private:
    std::unique_ptr<IResourceFactory> resourceFactory;

    std::unordered_map<std::string, std::shared_ptr<ITexture>> textures;
    std::unordered_map<std::string, std::shared_ptr<OpenGLShader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<Model>> models;

    std::shared_ptr<ITexture> debugTexture;
};

