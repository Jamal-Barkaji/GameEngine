#pragma once
#include <memory>
#include <string>


class ITexture;
class IMesh;

class IResourceFactory {
public:
    virtual ~IResourceFactory() = default;

    virtual std::shared_ptr<ITexture> createTexture(const std::string& path) = 0;
    virtual std::shared_ptr<IMesh> createMesh() = 0;
};