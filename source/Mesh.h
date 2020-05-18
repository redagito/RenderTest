#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Shader.h"

// Represents per-vertex data in model space
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture
{
    enum class Type
    {
        Diffuse,
        Specular,
        Normal,
        Height
    };

    GLuint id;
    // Either "diffuse_texture" or "specular_texture"
    // TODO Use enum
    std::string type;
    std::string fileName;
};

class Mesh
{
   public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures);
    void draw(Shader& shader) const;

   private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;

    void setup();
};