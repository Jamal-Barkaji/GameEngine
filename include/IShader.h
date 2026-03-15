#pragma once
#include <string>
#include <glm/glm.hpp>


class IShader {
public:
    virtual ~IShader() = default;

    virtual void bindShader() const = 0;
    virtual void unbindShader() const = 0;

    virtual void setInt(const std::string& name, int value) = 0;
    virtual void setFloat(const std::string& name, float value) = 0;
    virtual void setVec3(const std::string& name, const glm::vec3& value) = 0;
    virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;
    virtual int getUniformLocation(const std::string& name) = 0;
};