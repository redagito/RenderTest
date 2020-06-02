#pragma once

#include <memory>

#include "Model.h"
#include "RenderApplication.h"
#include "Shader.h"

// Displays 2 triangles
class ModelLoad : public RenderApplication
{
   private:
    std::vector<Model> models;
    std::unique_ptr<Shader> shader;

    const char* vertexCode = R"##(
	)##";

    const char* fragmentCode = R"##(
	)##";

    bool setup() override
    {
        models.push_back(Model{"data/backpack/backpack.obj"});
        shader = std::make_unique<Shader>(vertexCode, fragmentCode);
        return true;
    }

    void render() override
    {
        // Clear color buffer
        glClearColor(0.0f, 0.0f, 0.0f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (const auto& model : models)
        {
            model.draw(*shader);
        }
    }
};