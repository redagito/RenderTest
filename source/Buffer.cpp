#include "Buffer.h"

#include <stdexcept>

Buffer::~Buffer()
{
    if (m_id == 0)
        return;
    glDeleteBuffers(1, &m_id);
}

void Buffer::setData(const GLfloat* data, size_t componentsPerElement, size_t elementCount, GLbitfield usageFlags)
{
    if (data == nullptr)
        throw std::runtime_error{"data is null"};
    if (componentsPerElement < 1 || componentsPerElement > 4)
        throw std::runtime_error{"Invalid components per element value"};

    if (m_id == 0)
    {
        glCreateBuffers(1, &m_id);
    }

    m_componentsPerElement = componentsPerElement;
    m_componentSize = sizeof(GLfloat);
    m_elementCount = elementCount;
    m_type = GL_FLOAT;

    // Actual size of the data in bytes
    size_t dataSize = m_elementCount * componentsPerElement * m_componentSize;
    // Immutable storage
    // Use glBufferData for mutable storage
    glNamedBufferStorage(m_id, dataSize, data, usageFlags);
}

void Buffer::bind(GLuint index, GLenum target)
{
    glBindBuffer(target, m_id);
    glVertexAttribPointer(index, m_componentsPerElement, m_type, GL_FALSE, 0, nullptr);
}

size_t Buffer::getElementCount() const { return m_elementCount; }