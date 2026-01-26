#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValues.h"


class Shader {
    public:
        Shader();
        ~Shader();

        void CreateFromString(const char* vertexCode, const char* fragmentCode);
        void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

        static std::string ReadFile(const char* fileLocation);

        GLuint GetProjectLocation();
        GLuint GetModelLocation();
        GLuint GetViewLocation();
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

        void UseShader();
        void ClearShader();

    private:
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

        static std::string vShader;
        static std::string fShader;

        void CompileShader(const char* vertexCode, const char* fragmentCode);
        void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
