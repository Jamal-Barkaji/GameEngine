#pragma once

#include <memory>
#include <string>
#include <unordered_map>


class OpenGLTexture;
class OpenGLShader;
class Model;

class ResourceManager {
public:
    std::shared_ptr<OpenGLTexture> loadTexture(const std::string& path);
    std::shared_ptr<OpenGLTexture> getDebugTexture();

    std::shared_ptr<OpenGLShader>  loadShader(const std::string& vert, const std::string& frag);

    std::shared_ptr<Model>   loadModel(const std::string& path);

private:
    std::unordered_map<std::string, std::shared_ptr<OpenGLTexture>> textures;
    std::unordered_map<std::string, std::shared_ptr<OpenGLShader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<Model>> models;

    std::shared_ptr<OpenGLTexture> debugTexture;
};

