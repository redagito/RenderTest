#pragma once

#include <glad/glad.h>

class Buffer
{
public:
	Buffer();
	~Buffer();

	/**
	* @param data Data to be stored in the buffer
	* @param count Amount of values in data
	*/
	void setData(const GLfloat* data, size_t count, GLenum usage);

	void bind(GLuint index, GLenum target);

	size_t getSize() const;

	size_t getCount() const;

private:
	// Buffer id
	GLuint m_id = 0;
	// Buffer size, bytes
	size_t m_size = 0;
	// Size of single element in buffer
	size_t m_elementSize = 0;
	// Data type
	GLenum m_type = 0;
};