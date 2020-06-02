#pragma once

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <string>
#include <vector>

#include "Mesh.h"
#include "Shader.h"

/**
 * Basically a collection of meshes
 */
class Model
{
   public:
    Model(const std::string& path);

    void draw(Shader& shader) const;

   private:
    // Model data
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(const std::string& path);

    void processNode(aiNode* node, const aiScene* scene);
    // Builds Mesh from aiMesh
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);
};