#pragma once

#include <memory>

#include "RenderApplication.h"
#include "Shader.h"

// Displays 2 triangles
class ColorTriangle : public RenderApplication
{
   private:
    std::unique_ptr<Shader> m_shader;
    GLuint vertexArray = 0;
    GLuint vertexBuffer = 0;

    bool setup() override;

    void render() override;

   public:
    ~ColorTriangle();
};