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
