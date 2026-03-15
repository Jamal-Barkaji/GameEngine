#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "OpenGLMesh.h"
#include "OpenGLTexture.h"


class Model {
public:
    Model();
    ~Model();

    void addMesh(const std::shared_ptr<OpenGLMesh>& mesh);

    void renderModel();

    AABB getFullModelAABB() const;

private:
    bool loadModel(const std::string& fileName, ResourceManager& resources);
    void loadNode(aiNode* node, const aiScene* scene);
    void loadMesh(aiMesh* mesh, const aiScene* scene);
    void loadMaterials(const aiScene* scene, ResourceManager& resources);


    std::vector<std::shared_ptr<OpenGLMesh>> meshList;
    std::vector<std::shared_ptr<OpenGLTexture>> textureList;
    std::vector<unsigned int> meshToTex; // Which texture corresponds to which mesh


    friend class ResourceManager;
};
