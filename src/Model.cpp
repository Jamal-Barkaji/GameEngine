#include "Model.h"
#include "ResourceManager.h"
#include "glm/common.hpp"
#include "glm/vec3.hpp"


Model::Model() {

}

Model::~Model() {

}

void Model::addMesh(const std::shared_ptr<OpenGLMesh>& mesh) {
    meshList.push_back(mesh);
}

void Model::renderModel() {
    for (size_t i = 0; i < meshList.size(); i++) {
        if (i < meshToTex.size()) {
            unsigned int materialIndex = meshToTex[i];

            //TODO: Replace this logic with Material's bind shader method later
            if (materialIndex < textureList.size() && textureList[materialIndex]) {
                textureList[materialIndex]->bindTexture();
            }
        }

        if (meshList[i]) {
            meshList[i]->drawMesh();
        }
    }
}

bool Model::loadModel(const std::string& fileName, ResourceManager& resources) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if (!scene) {
        std::cerr << "Model failed to load: " << fileName << importer.GetErrorString() << std::endl;
        return false;
    }

    loadNode(scene->mRootNode, scene);

    loadMaterials(scene, resources);
    return true;
}

void Model::loadNode(aiNode* node, const aiScene* scene) {
    for (size_t i = 0; i < node->mNumMeshes; i++) {
        loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }

    for (size_t i = 0; i < node->mNumChildren; i++) {
        loadNode(node->mChildren[i], scene);
    }
}

void Model::loadMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<float> vertexData;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        // Grab position for AABB and OpenGL
        glm::vec3 pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

        // Add to the float buffer for the GPU
        vertexData.insert(vertexData.end(), { pos.x, pos.y, pos.z });

        if (mesh->mTextureCoords[0]) {
            vertexData.insert(vertexData.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
        } else {
            vertexData.insert(vertexData.end(), { 0.0f, 0.0f });
        }

        vertexData.insert(vertexData.end(), { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });
    }

    for (size_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    auto newMesh = std::make_shared<OpenGLMesh>();
    newMesh->createMesh(vertexData.data(), indices.data(), vertexData.size(), indices.size());

    AABB bounds = AABB::generateFromVertices(vertexData, 8);
    newMesh->setLocalBounds(bounds.min, bounds.max);

    meshList.push_back(newMesh);
    meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::loadMaterials(const aiScene* scene, ResourceManager& resources) {
    textureList.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* material = scene->mMaterials[i];

        std::shared_ptr<OpenGLTexture> tex = nullptr;

        if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
                std::string filename(path.data);
                size_t idx = filename.find_last_of("\\/");
                if (idx != std::string::npos) {
                    filename = filename.substr(idx + 1);
                }

                std::string texPath = "Assets/Textures/" + filename;
                tex = resources.loadTexture(texPath);
            }
        }

        if (!tex) {
            tex = resources.loadTexture("Assets/Textures/debugTexture.png");
        }

        textureList[i] = tex;
    }
}

AABB Model::getFullModelAABB() const {
    auto min = glm::vec3(FLT_MAX);
    auto max = glm::vec3(-FLT_MAX);
    for(auto& mesh : meshList) {
        min = glm::min(min, mesh->getLocalBounds().min);
        max = glm::max(max, mesh->getLocalBounds().max);
    }
    return {min, max};
}
