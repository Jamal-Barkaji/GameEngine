#pragma once

#include <memory>
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "IMesh.h"
#include "ITexture.h"
#include "PhysicsObject.h"


class ResourceManager;

class Model {
public:
    Model();
    ~Model();

    void addMesh(const std::shared_ptr<IMesh>& mesh);

    void renderModel();

    AABB getFullModelAABB() const;

private:
    bool loadModel(const std::string& fileName, ResourceManager& resources);
    void loadNode(aiNode* node, const aiScene* scene);
    void loadMesh(aiMesh* mesh, const aiScene* scene);
    void loadMaterials(const aiScene* scene, ResourceManager& resources);


    std::vector<std::shared_ptr<IMesh>> meshList;
    std::vector<std::shared_ptr<ITexture>> textureList;
    std::vector<unsigned int> meshToTex; // Which texture corresponds to which mesh


    friend class ResourceManager;
};
