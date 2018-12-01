#pragma once

#include <glad/glad.h>

GLuint createShaderObject(const char* shaderCode, GLenum shaderType);

GLuint createShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode);