#include "Skybox.h"

#include "GeometryGenerator.h"
#include "stb_image.h"


Skybox::Skybox(): skyboxTextureID(0), uniformProjection(0), uniformView(0) {
    // skyboxVAO = 0;
    // skyboxVBO = 0;
}

Skybox::Skybox(std::vector<std::string> faceLocations, std::shared_ptr<OpenGLShader> shader)
    : skyboxMesh(nullptr), skyboxShader(shader), uniformProjection(0), uniformView(0) {

    // Mesh Setup
    MeshData cubeData = GeometryGenerator::generateCube();

    skyboxMesh = std::make_unique<OpenGLMesh>();
    skyboxMesh->createMesh(cubeData.vertices.data(), cubeData.indices.data(), cubeData.vertices.size(), cubeData.indices.size());


    // OpenGLShader Setup
    // uniformProjection = skyboxShader->getProjectLocation();
    // uniformView = skyboxShader->getViewLocation();


    // Texture Setup
    glGenTextures(1, &skyboxTextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);

    int width, height, bitDepth;

    for (size_t i = 0; i < 6; i++) {
        unsigned char* texData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitDepth, 0);
        if (!texData) {
            std::cout << "Failed to find/load Skybox face: " << faceLocations[i]
                << " | STB Reason: " << stbi_failure_reason() << std::endl;
            return;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                     texData);
        stbi_image_free(texData);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Skybox::~Skybox() {
    // if (skyboxVAO) {
    //     glDeleteVertexArrays(1, &skyboxVAO);
    // }
    // if (skyboxVBO) {
    //     glDeleteBuffers(1, &skyboxVBO);
    // }
}

void Skybox::drawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    if (!skyboxMesh) return;

    viewMatrix = glm::mat4(glm::mat3(viewMatrix));

    glDepthMask(GL_FALSE);

    skyboxShader->bindShader();

    skyboxShader->setMat4("projection", projectionMatrix);
    skyboxShader->setMat4("view", viewMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);

    //TODO: create a validate() function in the shader class to check if the shader is ready to be used before drawing
    //skyboxShader->validate();

    skyboxMesh->drawMesh();

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glDepthMask(GL_TRUE);
}

unsigned int Skybox::getProjectionMatrix() {
    return uniformProjection;
}

unsigned int Skybox::getViewMatrix() {
    return uniformView;
}