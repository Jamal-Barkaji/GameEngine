#include "OpenGLResourceFactory.h"


std::shared_ptr<ITexture> OpenGLResourceFactory::instantiateTexture(const std::string& path) {
        return std::make_shared<OpenGLTexture>(path);
}

std::shared_ptr<IMesh> OpenGLResourceFactory::instantiateMesh() {
        return std::make_shared<OpenGLMesh>();
}

std::shared_ptr<ICubeMap> OpenGLResourceFactory::instantiateCubeMap(const std::vector<std::string>& faceLocations) {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int width, height, bitDepth;

        for (size_t i = 0; i < 6; i++) {
                unsigned char* texData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitDepth, 0);
                if (!texData) {
                        std::cout << "Failed to find/load Skybox face: " << faceLocations[i]
                                  << " | STB Reason: " << stbi_failure_reason() << std::endl;
                        continue;
                }

                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
                stbi_image_free(texData);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return std::make_shared<OpenGLCubeMap>(textureID);
}