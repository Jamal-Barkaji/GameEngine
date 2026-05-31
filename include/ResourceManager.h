#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "IResourceFactory.h"


class ITexture;
class IShader;
class Model;

class ResourceManager {
public:
    ResourceManager(std::unique_ptr<IResourceFactory> factory);


    std::shared_ptr<IMesh> requestMeshContainer();

    std::shared_ptr<ITexture> loadTexture(const std::string& path);
    std::shared_ptr<ITexture> getDebugTexture();

    std::shared_ptr<ICubeMap> loadCubeMap(const std::vector<std::string>& faceLocations);

    std::shared_ptr<IShader> loadShader(const std::string& vert, const std::string& frag);

    std::shared_ptr<Model> loadModel(const std::string& path);

private:
    std::unique_ptr<IResourceFactory> resourceFactory;

    std::unordered_map<std::string, std::shared_ptr<ITexture>> textures;
    std::shared_ptr<ITexture> debugTexture;

    std::unordered_map<std::string, std::shared_ptr<IShader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<Model>> models;
};

