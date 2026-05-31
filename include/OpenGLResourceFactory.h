#pragma once

#include "IResourceFactory.h"
#include "OpenGLCubeMap.h"
#include "stb_image.h"
#include "OpenGLTexture.h"
#include "OpenGLMesh.h"


class OpenGLResourceFactory : public IResourceFactory {
public:
    std::shared_ptr<ITexture> instantiateTexture(const std::string& path) override;

    std::shared_ptr<IMesh> instantiateMesh() override;

    std::shared_ptr<ICubeMap> instantiateCubeMap(const std::vector<std::string>& faceLocations) override;
};