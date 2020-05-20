#include "Mesh.h"

#include <cstddef>
#include <stdexcept>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices,
           const std::vector<Texture>& textures)
    : vertices(vertices), indices(indices), textures(textures)
{
    setup();
}

void Mesh::draw(Shader& shader) const
{
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;

    // Bind all textures in the mesh to the shader
    for (GLuint i = 0; i < textures.size(); ++i)
    {
        // Activate texture unit
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures.at(i).type;

        // Texture type
        if (name == "texture_diffuse")
        {
            number = std::to_string(diffuseNr);
            ++diffuseNr;
        }
        else if (name == "texture_specular")
        {
            number = std::to_string(specularNr);
            ++specularNr;
        }
        else
        {
            throw std::runtime_error{"Invalid texture type"};
        }

        // Bind textures to shader
        // Set sampler to texture unit
        auto uniformName = "material." + name + number;

        shader.set(uniformName, i);
        // Bind texture to index
        glBindTexture(GL_TEXTURE_2D, textures.at(i).id);
    }

    // Reset active texture unit
    glActiveTexture(GL_TEXTURE0);

    // Draw mesh
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh::setup()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    // Write data
    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type), vertices.data(),
                 GL_STATIC_DRAW);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type), indices.data(),
                 GL_STATIC_DRAW);

    // Set attributes
    // Vertex buffer has attributes for vertices, normals and texcoords
    // Layout is v0, v1, v2, n0, n1, n2, t0, t1
    // All values are float
    // Vertices at index 0
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Normals at index 1, requires offset
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)offsetof(Vertex, normal));

    // Texture coordinates at index 2, requires offset
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)offsetof(Vertex, texCoords));

    // Disable vao
    glBindVertexArray(0);
}