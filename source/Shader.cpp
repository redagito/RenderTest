#include "Shader.h"

#include <vector>
#include <iostream>

GLuint createShaderObject(const char* shaderCode, GLenum shaderType)
{
	GLuint shaderObject = glCreateShader(shaderType);

	// Compile shader
	std::cout << "Compiling shader" << std::endl;
	glShaderSource(shaderObject, 1, &shaderCode, NULL);
	glCompileShader(shaderObject);

	// Check shader
	GLint result = GL_FALSE;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

	int infoLogLength = 0;
	glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> infoLog(infoLogLength + 1);
		glGetShaderInfoLog(shaderObject, infoLogLength, NULL, infoLog.data());
		std::cout << infoLog.data() << std::endl;
	}
	if (result == GL_FALSE)
	{
		glDeleteShader(shaderObject);
		throw std::runtime_error{ "Failed to compile shader object" };
	}

	return shaderObject;
}

GLuint createShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode)
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
	if (infoLogLength > 0) {
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
		throw std::runtime_error{ "Failed to link shader program" };
	}

	return shaderProgram;
}