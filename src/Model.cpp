#include "Model.h"
#include "ResourceManager.h"


Model::Model() {

}

Model::~Model() {

}

void Model::addMesh(const std::shared_ptr<Mesh>& mesh) {
    meshList.push_back(mesh);
}

void Model::renderModel() {
    for (size_t i = 0; i < meshList.size(); i++) {
        if (i < meshToTex.size()) {
            unsigned int materialIndex = meshToTex[i];

            //TODO: Replace this logic with Material's bind shader method later
            if (materialIndex < textureList.size() && textureList[materialIndex]) {
                textureList[materialIndex]->useTexture();
            }
        }

        if (meshList[i]) {
            meshList[i]->DrawMesh();
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
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        vertices.insert(vertices.end(), {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        });
        if (mesh->mTextureCoords[0]) {
            vertices.insert(vertices.end(), {
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            });
        } else {
            vertices.insert(vertices.end(), {0.0f, 0.0f});
        }
        vertices.insert(vertices.end(), {
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        });
    }
    for (size_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    auto newMesh = std::make_shared<Mesh>();
    newMesh->CreateMesh(vertices.data(), indices.data(), vertices.size(), indices.size());
    meshList.push_back(newMesh);
    meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::loadMaterials(const aiScene* scene, ResourceManager& resources) {
    textureList.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* material = scene->mMaterials[i];

        std::shared_ptr<Texture> tex = nullptr;

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
            tex = resources.loadTexture("C:/Users/barka/CLionProjects/GameEngine/Assets/Textures/debugTexture.png");
        }

        textureList[i] = tex;
    }
}
