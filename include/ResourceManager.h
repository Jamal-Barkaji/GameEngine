#pragma once

#include <memory>
#include <string>
#include <unordered_map>


class Texture;
class Shader;
class Model;

class ResourceManager {
public:
    std::shared_ptr<Texture> loadTexture(const std::string& path);
    std::shared_ptr<Texture> getDebugTexture();

    std::shared_ptr<Shader>  loadShader(const std::string& vert, const std::string& frag);

    std::shared_ptr<Model>   loadModel(const std::string& path);

private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<Model>> models;

    std::shared_ptr<Texture> debugTexture;
};

