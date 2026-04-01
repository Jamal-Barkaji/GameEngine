#pragma once


class IShadowMap {
public:
    virtual ~IShadowMap() = default;
    virtual bool init(unsigned int width, unsigned int height) = 0;
    virtual void write() = 0;
    virtual void read(unsigned int textureUnit) = 0;
    virtual unsigned int getShadowWidth() = 0;
    virtual unsigned int getShadowHeight() = 0;
};