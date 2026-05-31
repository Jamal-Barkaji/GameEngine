#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ICubeMap.h"


class ITexture;
class IMesh;

class IResourceFactory {
public:
    virtual ~IResourceFactory() = default;

    virtual std::shared_ptr<ITexture> instantiateTexture(const std::string& path) = 0;
    virtual std::shared_ptr<IMesh> instantiateMesh() = 0;
    virtual std::shared_ptr<ICubeMap> instantiateCubeMap(const std::vector<std::string>& faceLocations) = 0;
};