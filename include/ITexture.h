#pragma once


class ITexture {
public:
    virtual ~ITexture() = default;

    virtual bool loadTexture() = 0;
    virtual bool loadTextureA() = 0;

    virtual void bindTexture() = 0;
    virtual void bindTexture(unsigned int slot) = 0;
    virtual void unbindTexture() = 0;
};
