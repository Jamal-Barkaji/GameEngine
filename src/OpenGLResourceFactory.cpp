#include "OpenGLResourceFactory.h"


std::shared_ptr<ITexture> OpenGLResourceFactory::createTexture(const std::string& path) {
        return std::make_shared<OpenGLTexture>(path);
}

std::shared_ptr<IMesh> OpenGLResourceFactory::createMesh() {
        return std::make_shared<OpenGLMesh>();
}