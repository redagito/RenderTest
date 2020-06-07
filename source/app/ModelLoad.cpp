#include "app/ModelLoad.h"

bool ModelLoad::setup()
{
    const char* vertexCode = R"##(
	)##";

    const char* fragmentCode = R"##(
	)##";

    models.push_back(Model{"data/backpack/backpack.obj"});
    shader = std::make_unique<Shader>(vertexCode, fragmentCode);
    return true;
}

void ModelLoad::render()
{
    // Clear color buffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto& model : models)
    {
        model.draw(*shader);
    }
}