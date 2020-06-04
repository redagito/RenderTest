#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "RenderApplication.h"
#include "Shader.h"
#include "Texture.h"

// Cube vertices, 36 entries
// clang-format off
const float cubeVertices[] = {
    // x, y, z, u, v
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
// clang-format on

class CubePerspective : public RenderApplication
{
   private:
    std::unique_ptr<Shader> shader;
    Texture texContainer;
    GLuint vao = 0;
    GLuint vbo = 0;

    bool setup() override
    {
        static const char* vertexCode = R"##(
#version 460 core

layout (location = 0) in vec3 vp_ms;
layout (location = 1) in vec2 uv;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	texCoord = uv;
    // Matrix multiplication is read left to right
	gl_Position = projection * view * model * vec4(vp_ms, 1.f);
}
)##";

        static const char* fragmentCode = R"##(
#version 460 core

in vec2 texCoord;

out vec4 color;

uniform sampler2D baseTex;

void main()
{
	color = texture(baseTex, texCoord);
}

)##";

        // Shader
        shader = std::make_unique<Shader>(vertexCode, fragmentCode);

        // Texture
        texContainer.id = textureFromFile("wall.jpg", "data/texture/");

        glCreateBuffers(1, &vbo);
        glNamedBufferData(vbo, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // x/y/z
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(GLfloat) * 5, nullptr);
        // u/v
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(GLfloat) * 5, (void*)(sizeof(GLfloat) * 3));

        glBindVertexArray(0);

        // Clear color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);

        return true;
    }

    void render() override
    {
        static float timeAcc = 0;
        timeAcc += getTimeDelta();

        // Model matrix
        glm::mat4 model{1.f};
        // Rotation
        model = glm::rotate(model, glm::radians(timeAcc * 10.f), {1.f, 0.3f, 0.7f});

        // View matrix
        glm::mat4 view{1.f};
        view = glm::translate(view, {0.f, 0.f, -3.f});

        // Projection
        auto aspectRatio = (float)getWidth() / (float)getHeight();
        glm::mat4 projection = glm::perspective(glm::radians(45.f), aspectRatio, 0.1f, 100.f);

        // Clear framebuffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader
        shader->setActive();

        // Transformation data for shader
        shader->set("model", model);
        shader->set("view", view);
        shader->set("projection", projection);

        // Texture
        // Activate the binding location
        glActiveTexture(GL_TEXTURE0);
        // Bind the actual texture to active location
        glBindTexture(GL_TEXTURE_2D, texContainer.id);
        // Set texture location manually
        shader->set("baseTex", 0);

        glBindVertexArray(vao);
        auto vertexCount = sizeof(cubeVertices) / sizeof(GLfloat) / 5;
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    }

   public:
    ~CubePerspective()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }
};