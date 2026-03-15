#pragma once


class ITexture {
public:
    virtual ~ITexture() = default;

    virtual void bindTexture() = 0;
};
