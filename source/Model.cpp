#include "Model.h"

#include <SOIL2/SOIL2.h>

#include <stdexcept>

GLuint textureFromFile(const std::string& fileName, const std::string& directory)
{
    // Load with soil2
    auto filePath = directory + "/" + fileName;

    GLuint id = SOIL_load_OGL_texture(fileName.c_str(), 0, 0, 0);
    if (id == 0)
        throw std::runtime_error{"Failed to load texture " + filePath};

    glBindTexture(GL_TEXTURE_2D, id);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return id;
}

Model::Model(const std::string& path) { loadModel(path); }

void Model::draw(Shader& shader)
{
    // Draw each mesh
    // TODO Camera for culling?
    for (const auto& mesh : meshes)
    {
        mesh.draw(shader);
    }
}

void Model::loadModel(const std::string& path)
{
    Assimp::Importer importer;
    auto scene = importer.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);
    // Check error
    if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
    {
        throw std::runtime_error{importer.GetErrorString()};
    }

    // Directory of the loaded file
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // Process all meshes
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        // Meshes are stored in the scene, each node has a list
        // of mesh indices
        // TODO Range check
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    // Process all children of the mesh
    // TODO Probably bad idea for meshes with large amount of children
    //      Change this to be non-recursive
    for (unsigned int i = 0; i < node->mNumChildren; ++i)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);

    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    textures.reserve(10);

    if (mesh->mNormals == nullptr)
        throw std::runtime_error{"Mesh is missing normal data"};

    // Per vertex data
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;
        vertex.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        vertex.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};

        // Texture coordinates
        // Up to 8 different texture coordinates allowed per vertex
        // Only use the first
        if (mesh->mTextureCoords[0] != nullptr)
        {
            vertex.texCoords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        }
        else
        {
            vertex.texCoords = {0.f, 0.f};
        }

        vertices.push_back(vertex);
    }

    // Indices, stored per face
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        auto face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Material
    if (mesh->mMaterialIndex >= 0)
    {
        auto material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

        // Insert into textures
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh{vertices, indices, textures};
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < material->GetTextureCount(type); ++i)
    {
        // Path to the texture
        aiString fileName;
        material->GetTexture(type, i, &fileName);

        // Load texture
        Texture texture;
        texture.id = textureFromFile(fileName.C_Str(), directory);
        // TODO Just map from aiTextureType
        texture.type = typeName;
        texture.fileName = fileName.C_Str();
        textures.push_back(texture);
    }

    return textures;
}