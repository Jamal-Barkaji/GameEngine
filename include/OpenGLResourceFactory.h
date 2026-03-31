#pragma once
#include "IResourceFactory.h"
#include "OpenGLTexture.h"
#include "OpenGLMesh.h"


class OpenGLResourceFactory : public IResourceFactory {
public:
    std::shared_ptr<ITexture> createTexture(const std::string& path) override;

    std::shared_ptr<IMesh> createMesh() override;
};