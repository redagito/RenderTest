#pragma once

#include "RenderApplication.h"

// Displays 2 triangles
class HelloTriangle : public RenderApplication
{
   private:
    Buffer m_vertexBuffer;
    GLuint m_shader = 0;

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

void main(){
	color = vec4(1.f, 0.f, 0.f, 1.f);
}
	)##";

    bool setup() override
    {
        // Vertices
        static const GLfloat vertices[][2] = {{-0.9f, -0.9f}, {0.85f, -0.9f}, {-0.9f, 0.85f},
                                              {0.9f, -0.85f}, {0.9f, 0.9f},   {-0.85f, 0.9f}};

        m_vertexBuffer.setData((GLfloat*)vertices, 2, 6, 0);

        // Vertex array object
        GLuint vertexArray;
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        m_shader = createShaderProgram(vertexCode, fragmentCode);
        return true;
    }

    void render() override
    {
        // Clear color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_shader);

        // Draw
        glEnableVertexAttribArray(0);
        m_vertexBuffer.bind(0, GL_ARRAY_BUFFER);

        glDrawArrays(GL_TRIANGLES, 0, m_vertexBuffer.getElementCount());
        glDisableVertexAttribArray(0);
    }

   public:
    ~HelloTriangle() { glDeleteProgram(m_shader); }
};