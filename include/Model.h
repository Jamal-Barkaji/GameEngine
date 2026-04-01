#pragma once

#include <memory>
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "IMesh.h"
#include "IShader.h"
#include "ITexture.h"
#include "Material.h"
#include "PhysicsObject.h"


class ResourceManager;

class Model {
public:
    Model();
    ~Model();

    void addMesh(const std::shared_ptr<IMesh>& mesh);

    void renderModel(IShader& shader);

    AABB getFullModelAABB() const;

private:
    bool loadModel(const std::string& fileName, ResourceManager& resources);
    void loadNode(aiNode* node, const aiScene* scene, ResourceManager& resources);
    void loadMesh(aiMesh* mesh, const aiScene* scene, ResourceManager& resources);
    void loadMaterials(const aiScene* scene, ResourceManager& resources);


    std::vector<std::shared_ptr<IMesh>> meshList;
    std::vector<std::shared_ptr<Material>> materialList;
    std::vector<unsigned int> meshToMat; // Which material corresponds to which mesh


    friend class ResourceManager;
};
