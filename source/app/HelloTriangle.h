#pragma once

#include <memory>

#include "RenderApplication.h"
#include "Shader.h"

// Displays 2 triangles
class HelloTriangle : public RenderApplication
{
   private:
    std::unique_ptr<Shader> m_shader;
    GLuint vertexArray = 0;
    GLuint vertexBuffer = 0;

    bool setup() override
    {
        const char* vertexCode = R"##(
#version 460 core

layout(location = 0) in vec2 vertexPosition_normalizedScreenSpace;

void main(){
	gl_Position.xy = vertexPosition_normalizedScreenSpace;
	gl_Position.w = 1.f;
}
	    )##";

        const char* fragmentCode = R"##(
#version 460 core

out vec4 color;

uniform vec3 base_color;

void main(){
	color = vec4(base_color, 1.f);
}
	    )##";

        // Vertices
        static const GLfloat vertices[][2] = {{-0.9f, -0.9f}, {0.85f, -0.9f}, {-0.9f, 0.85f},
                                              {0.9f, -0.85f}, {0.9f, 0.9f},   {-0.85f, 0.9f}};

        // Create vertex buffer
        glCreateBuffers(1, &vertexBuffer);
        glNamedBufferData(vertexBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Vertex array object
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindVertexArray(0);

        m_shader = std::make_unique<Shader>(vertexCode, fragmentCode);
        return true;
    }

    void render() override
    {
        // Clear color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        glBindVertexArray(vertexArray);
        glEnableVertexAttribArray(0);

        m_shader->setActive();
        m_shader->set("base_color", {0.f, 1.f, 1.f});

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(0);
    }

   public:
    ~HelloTriangle()
    {
        glDeleteVertexArrays(1, &vertexArray);
        glDeleteBuffers(1, &vertexBuffer);
    }
};