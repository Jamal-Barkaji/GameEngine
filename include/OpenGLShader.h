#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValues.h"
#include "IShader.h"


class ResourceManager;

class OpenGLShader : public IShader {
public:
    OpenGLShader();
    ~OpenGLShader() override;

    static std::string readFile(const char* fileLocation);

    // GLuint getProjectLocation();
    // GLuint getModelLocation();
    // GLuint getViewLocation();
    // GLuint getAmbientIntensityLocation();
    // GLuint getAmbientColourLocation();
    // GLuint getDiffuseIntensityLocation();
    // GLuint getDirectionLocation();
    // GLuint getSpecularIntensityLocation();
    // GLuint getShininessLocation();
    // GLuint getAlbedoLocation();
    // GLuint getEyePositionLocation();

    // void setDirectionalLight(DirectionalLight* dLight);
    // void setPointLights(PointLight* pLight, unsigned int lightCount);
    // void setSpotLights(SpotLight* sLight, unsigned int lightCount);
    // void setTexture(GLuint textureUnit);
    // void setDirectionalShadowMap(GLuint textureUnit);
    // void setDirectionalLightTransform(glm::mat4* lTransform);

    void bindShader() const override;
    void unbindShader() const override;

    void setInt(const std::string& name, int value) override;
    void setFloat(const std::string& name, float value) override;
    void setVec3(const std::string& name, const glm::vec3& value) override;
    void setMat4(const std::string& name, const glm::mat4& value) override;
    int getUniformLocation(const std::string& name) override;

private:
    void createFromString(const char* vertexCode, const char* fragmentCode);
    void createFromFiles(const char* vertexLocation, const char* fragmentLocation);

    void compileShader(const char* vertexCode, const char* fragmentCode);
    void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

    std::unordered_map<std::string, int> locationCache;

    int pointLightCount;
    int spotLightCount;

    GLuint shaderID, uniformProjection, uniformView, uniformEyePosition,
        uniformSpecularIntensity, uniformShininess,
        uniformTexture,
        uniformDirectionalLightTransform, uniformDirectionalShadowMap;

    GLint uniformModel;

    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformDirection;
    } uniformDirectionalLight;

    GLuint uniformPointLightCount;

    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;
    } uniformPointLight[MAX_POINT_LIGHTS];

    GLuint uniformSpotLightCount;

    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;

        GLuint uniformDirection;
        GLuint uniformEdge;
    } uniformSpotLight[MAX_SPOT_LIGHTS];


    friend class ResourceManager;
};
