#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>

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
        GLuint getDiffuseIntesityLocation();
        GLuint getDirectionLocation();

        void UseShader();
        void ClearShader();

    private:
        GLuint shaderID, uniformProjection, uniformView,
            uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection;

        GLint uniformModel;
        static std::string vShader;
        static std::string fShader;

        void CompileShader(const char* vertexCode, const char* fragmentCode);
        void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
