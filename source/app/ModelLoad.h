#pragma once

#include "Model.h"
#include "RenderApplication.h"

// Displays 2 triangles
class ModelLoad : public RenderApplication
{
   private:
    std::vector<Model> models;

    const char* vertexCode = R"##(
	)##";

    const char* fragmentCode = R"##(
	)##";

    bool setup() override
    {
        models.push_back(Model{"data/backpack/backpack.obj"});
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
    ~ModelLoad() { glDeleteProgram(m_shader); }
};