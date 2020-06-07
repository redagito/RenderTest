#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::setLookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
{
    this->position = position;
    this->target = target;
    this->up = up;
    view = glm::lookAt(position, target, up);
}

void Camera::setPosition(const glm::vec3& position)
{
    this->position = position;
    view = glm::lookAt(position, target, up);
}

void Camera::setTarget(const glm::vec3& target)
{
    this->target = target;
    view = glm::lookAt(position, target, up);
}

void Camera::setUp(const glm::vec3& up)
{
    this->up = up;
    view = glm::lookAt(position, target, up);
}

const glm::mat4& Camera::getView() const { return view; }