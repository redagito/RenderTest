#pragma once

#include <glad/glad.h>

#include <string>

GLuint createShaderObject(const char* shaderCode, GLenum shaderType);

GLuint createShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode);

class Shader
{
   public:
    GLuint id;
};