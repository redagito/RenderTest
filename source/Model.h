#pragma once

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <string>
#include <vector>

#include "Mesh.h"
#include "Shader.h"

// Texture loading
GLuint textureFromFile(const std::string& fileName, const std::string& directory);

class Model
{
   public:
    Model(const std::string& path);

    void draw(Shader& shader);

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