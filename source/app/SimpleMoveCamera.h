#pragma once

#include "Camera.h"
#include "RenderApplication.h"
#include "Shader.h"
#include "Texture.h"

class SimpleMoveCamera : public RenderApplication
{
   private:
    std::unique_ptr<Shader> shader;
    Texture texContainer;
    Camera camera;
    glm::vec3 cameraFront = glm::vec3{0.f, 0.f, -1.f};
    GLuint vao = 0;
    GLuint vbo = 0;

    bool setup() override;

    void render() override;

   public:
    ~SimpleMoveCamera();
};