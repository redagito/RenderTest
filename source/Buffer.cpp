#include "Buffer.h"

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_id);
}

void Buffer::setData(const GLfloat* data, size_t count, GLenum usage)
{
	if (m_id == 0)
	{
		glCreateBuffers(1, &m_id);
	}

	m_size = count * sizeof(GLfloat);
	m_elementSize = sizeof(GLfloat);
	m_type = GL_FLOAT;

	glNamedBufferStorage(m_id, m_size, data, usage);
}

void Buffer::bind(GLuint index, GLenum target)
{
	glBindBuffer(target, m_id);
	glVertexAttribPointer(index, m_size / m_elementSize / 3, m_type, GL_FALSE, 0, nullptr);
}

size_t Buffer::getSize() const
{
	return m_size;
}

size_t Buffer::getCount() const
{
	return m_size / m_elementSize;
}
