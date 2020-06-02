#pragma once

#include <glad/glad.h>

#include <string>

// Texture loading
GLuint textureFromFile(const std::string& fileName, const std::string& directory);

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