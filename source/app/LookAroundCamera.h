#pragma once

#include "Camera.h"
#include "RenderApplication.h"
#include "Shader.h"
#include "Texture.h"

/**
 * Mouse controlled camera that can look around
 */
class LookAroundCamera : public RenderApplication
{
   private:
    std::unique_ptr<Shader> shader;
    Texture texContainer;
    Camera camera;
    // Camera view direction
    // Left / right rotation
    float yaw = -90.f;
    // Up / down rotation
    float pitch = 0.f;

    GLuint vao = 0;
    GLuint vbo = 0;

    bool setup() override;

    void render() override;

   public:
    ~LookAroundCamera();
};