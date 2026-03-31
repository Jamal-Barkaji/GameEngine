#include "ResourceManager.h"
#include "OpenGLTexture.h"
#include "OpenGLShader.h"
#include "Model.h"

#include <iostream>


ResourceManager::ResourceManager(std::unique_ptr<IResourceFactory> rf) : resourceFactory(std::move(rf)) {}


std::shared_ptr<IMesh> ResourceManager::createMesh() {
    return resourceFactory->createMesh();
}

std::shared_ptr<ITexture> ResourceManager::loadTexture(const std::string& path) {
    if (textures.count(path)) return textures[path];

    auto tex = resourceFactory->createTexture(path);
    if (!tex->loadTexture()) {
        std::cerr << "Failed to load texture: " << path << "\n";

        textures[path] = getDebugTexture();
        return textures[path];
    }

    textures[path] = tex;
    return tex;
}

std::shared_ptr<ITexture> ResourceManager::getDebugTexture() {
    if (!debugTexture) {
        auto tex = resourceFactory->createTexture("Assets/Textures/debugTexture.png");
        debugTexture->loadTexture();
    }
    return debugTexture;
}

std::shared_ptr<OpenGLShader> ResourceManager::loadShader(const std::string& vert, const std::string& frag) {
    std::string key = vert + "+" + frag;
    if (shaders.count(key)) return shaders[key];

    auto shader = std::make_shared<OpenGLShader>();
    shader->createFromFiles(vert.c_str(), frag.c_str());

    shaders[key] = shader;
    return shader;
}

std::shared_ptr<Model> ResourceManager::loadModel(const std::string& path) {
    if (models.count(path)) return models[path];

    auto model = std::make_shared<Model>();
    if (!model->loadModel(path, *this)) {
        std::cerr << "Failed to load model: " << path << "\n";
        return nullptr;
    }

    models[path] = model;
    return model;
}
