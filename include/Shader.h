#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValues.h"


class ResourceManager;

class Shader {
public:
    Shader();
    ~Shader();

    static std::string readFile(const char* fileLocation);

    GLuint getProjectLocation();
    GLuint getModelLocation();
    GLuint getViewLocation();
    GLuint getAmbientIntensityLocation();
    GLuint getAmbientColourLocation();
    GLuint getDiffuseIntensityLocation();
    GLuint getDirectionLocation();
    GLuint getSpecularIntensityLocation();
    GLuint getShininessLocation();
    GLuint getAlbedoLocation();
    GLuint getEyePositionLocation();

    void setDirectionalLight(DirectionalLight* dLight);
    void setPointLights(PointLight* pLight, unsigned int lightCount);
    void setSpotLights(SpotLight* sLight, unsigned int lightCount);
    void setTexture(GLuint textureUnit);
    void setDirectionalShadowMap(GLuint textureUnit);
    void setDirectionalLightTransform(glm::mat4* lTransform);

    void useShader();
    void clearShader();

private:
    void createFromString(const char* vertexCode, const char* fragmentCode);
    void createFromFiles(const char* vertexLocation, const char* fragmentLocation);

    void compileShader(const char* vertexCode, const char* fragmentCode);
    void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);


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
