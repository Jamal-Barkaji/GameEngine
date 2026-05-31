#pragma once

class ICubeMap {
public:
    virtual ~ICubeMap() = default;
    
    virtual void bind(unsigned int slot) = 0;

    void bind() {
        bind(0);
    }

    virtual void unbind() = 0;
};