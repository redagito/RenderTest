#pragma once

#include <memory>

#include "Buffer.h"
#include "RenderApplication.h"
#include "Shader.h"

// Displays 2 triangles
class HelloTriangle : public RenderApplication
{
   private:
    Buffer m_vertexBuffer;
    std::unique_ptr<Shader> m_shader;

    bool setup() override
    {
        const char* vertexCode = R"##(
#version 460 core

layout(location = 0) in vec3 vertexPosition_modelspace;

void main(){
	gl_Position.xyz = vertexPosition_modelspace;
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

        m_vertexBuffer.setData((GLfloat*)vertices, 2, 6, 0);

        // Vertex array object
        GLuint vertexArray;
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        m_shader = std::make_unique<Shader>(vertexCode, fragmentCode);
        return true;
    }

    void render() override
    {
        // Clear color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        glEnableVertexAttribArray(0);
        m_vertexBuffer.bind(0, GL_ARRAY_BUFFER);

        m_shader->setActive();
        m_shader->set("base_color", {0.f, 1.f, 1.f});

        glDrawArrays(GL_TRIANGLES, 0, m_vertexBuffer.getElementCount());
        glDisableVertexAttribArray(0);
    }

   public:
    ~HelloTriangle() {}
};