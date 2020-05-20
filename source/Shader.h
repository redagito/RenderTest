#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader
{
   public:
    Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
    ~Shader();

    void setActive() const;

    void set(const std::string& name, const int value);
    void set(const std::string& name, const unsigned int value);
    void set(const std::string& name, const float value);
    void set(const std::string& name, const glm::vec2& value);
    void set(const std::string& name, const glm::vec3& value);
    void set(const std::string& name, const glm::vec4& value);

   private:
    int getUniformLocation(const std::string& name) const;

    GLuint id = 0;
    mutable std::unordered_map<std::string, int> uniformLocations;
};

GLuint createShaderObject(const std::string& code, GLenum shaderType);
GLuint createShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);