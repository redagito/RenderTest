#include "Shader.h"

#include <iostream>
#include <vector>

Shader::Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
{
    id = createShaderProgram(vertexShaderCode, fragmentShaderCode);
}

Shader::~Shader()
{
    if (id == 0)
        return;
    glDeleteProgram(id);
}

void Shader::setActive() const { glUseProgram(id); }

void Shader::set(const std::string& name, const int value) { glUniform1i(getUniformLocation(name), value); }

void Shader::set(const std::string& name, const unsigned int value) { glUniform1ui(getUniformLocation(name), value); }

void Shader::set(const std::string& name, const float value) { glUniform1f(getUniformLocation(name), value); }

void Shader::set(const std::string& name, const glm::vec2& value)
{
    glUniform2f(getUniformLocation(name), value.x, value.y);
}

void Shader::set(const std::string& name, const glm::vec3& value)
{
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::set(const std::string& name, const glm::vec4& value)
{
    glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

int Shader::getUniformLocation(const std::string& name) const
{
    auto iter = uniformLocations.find(name);
    if (iter != uniformLocations.end())
    {
        return iter->second;
    }
    int index = glGetUniformLocation(id, name.c_str());
    if (index < 0)
        throw std::runtime_error{"Uniform does not exist: " + name};
    uniformLocations[name] = index;
    return index;
}

GLuint createShaderObject(const std::string& code, GLenum shaderType)
{
    GLuint shaderObject = glCreateShader(shaderType);

    // Compile shader
    std::cout << "Compiling shader" << std::endl;
    const char* temp = code.c_str();
    glShaderSource(shaderObject, 1, &temp, NULL);
    glCompileShader(shaderObject);

    // Check shader
    GLint result = GL_FALSE;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

    int infoLogLength = 0;
    glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> infoLog(infoLogLength + 1);
        glGetShaderInfoLog(shaderObject, infoLogLength, NULL, infoLog.data());
        std::cout << infoLog.data() << std::endl;
    }
    if (result == GL_FALSE)
    {
        glDeleteShader(shaderObject);
        throw std::runtime_error{"Failed to compile shader object"};
    }

    return shaderObject;
}

GLuint createShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
{
    GLuint vertexShader = createShaderObject(vertexShaderCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = createShaderObject(fragmentShaderCode, GL_FRAGMENT_SHADER);

    // Link the program
    std::cout << "Linking shader program" << std::endl;
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check the program
    GLint result = GL_FALSE;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);

    int infoLogLength = 0;
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> infoLog(infoLogLength + 1);
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, &infoLog[0]);
        std::cout << infoLog.data() << std::endl;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (result == GL_FALSE)
    {
        glDeleteProgram(shaderProgram);
        throw std::runtime_error{"Failed to link shader program"};
    }

    return shaderProgram;
}