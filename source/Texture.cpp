#include "Texture.h"

#include <SOIL2/SOIL2.h>

#include <stdexcept>

GLuint textureFromFile(const std::string& fileName, const std::string& directory)
{
    // Load with soil2
    auto filePath = directory + "/" + fileName;

    GLuint id = SOIL_load_OGL_texture(filePath.c_str(), 0, 0, 0);
    if (id == 0)
        throw std::runtime_error{"Failed to load texture " + filePath};

    glBindTexture(GL_TEXTURE_2D, id);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return id;
}