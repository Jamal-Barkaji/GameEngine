#include "ResourceManager.h"
#include "Texture.h"
#include "Shader.h"
#include "Model.h"

#include <iostream>

std::shared_ptr<Texture> ResourceManager::loadTexture(const std::string& path) {
    if (textures.count(path)) return textures[path];

    auto tex = std::make_shared<Texture>(path);
    if (!tex->loadTexture()) {
        std::cerr << "Failed to load texture: " << path << "\n";
        return getDebugTexture();
    }

    textures[path] = tex;
    return tex;
}

std::shared_ptr<Texture> ResourceManager::getDebugTexture() {
    if (!debugTexture) {
        debugTexture = std::make_shared<Texture>("Assets/Textures/debugTexture.png");
        debugTexture->loadTexture();
    }
    return debugTexture;
}

std::shared_ptr<Shader> ResourceManager::loadShader(const std::string& vert, const std::string& frag) {
    std::string key = vert + "+" + frag;
    if (shaders.count(key)) return shaders[key];

    auto shader = std::make_shared<Shader>();
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
