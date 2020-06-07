#pragma once

#include <glm/glm.hpp>

class Camera
{
   public:
    void setLookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
    void setPosition(const glm::vec3& position);
    void setTarget(const glm::vec3& target);
    void setUp(const glm::vec3& up);

    const glm::vec3& getPosition() const;
    const glm::vec3& getUp() const;

    const glm::mat4& getView() const;

   private:
    // Position in world space
    glm::vec3 position = glm::vec3{0.f, 0.f, 0.f};
    // Target position in world space
    glm::vec3 target = glm::vec3{0.f, 0.f, -1.f};
    // Camera up vector
    glm::vec3 up = glm::vec3{0.f, 1.f, 0.f};
    // View matrix
    glm::mat4 view;
};