#pragma once

#include <memory>

#include "RenderApplication.h"
#include "Shader.h"

/**
 * Display 2 colored triangles
 */
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