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

    bool setup() override;

    void render() override;
};