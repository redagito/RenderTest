#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "RenderApplication.h"
#include "Shader.h"
#include "Texture.h"

class HelloPerspective : public RenderApplication
{
   private:
    std::unique_ptr<Shader> shader;
    Texture texContainer;
    GLuint vao = 0;
    GLuint vbo = 0;

    bool setup() override;

    void render() override;

   public:
    ~HelloPerspective();
};