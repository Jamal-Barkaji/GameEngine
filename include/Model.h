#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"


class Model {
public:
    Model();
    ~Model();

    void renderModel();

private:
    bool loadModel(const std::string& fileName, ResourceManager& resources);
    void loadNode(aiNode* node, const aiScene* scene);
    void loadMesh(aiMesh* mesh, const aiScene* scene);
    void loadMaterials(const aiScene* scene, ResourceManager& resources);


    std::vector<std::shared_ptr<Mesh>> meshList;
    std::vector<std::shared_ptr<Texture>> textureList;
    std::vector<unsigned int> meshToTex; // Which texture corresponds to which mesh


    friend class ResourceManager;
};
