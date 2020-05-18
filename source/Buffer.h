#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <vector>

/**
 * A buffer stores a number of elements consisting of 1 or more components of a specific size in bytes
 * The size of a single element in bytes is elementSize = componentsPerElement * componentSize
 * The total size of the buffer in bytes is bufferSize = elementSize * elementCount
 */
class Buffer
{
   public:
    Buffer() = default;
    ~Buffer();

    /**
     * @param data Data to be stored in the buffer
     * @param componentsPerElement Components in a single element
     * @param componentSize Size of a single component in bytes
     * @param elementCount Total number of elements
     */
    void setData(const GLfloat* data, size_t componentsPerElement, size_t elementCount, GLbitfield usageFlags);

    /**
     * @param index Index of the attribute in the shader
     * @param target
     */
    void bind(GLuint index, GLenum target);

    /**
     * @return Number of elements in the buffer
     */
    size_t getElementCount() const;

   private:
    // Buffer id
    GLuint m_id = 0;
    // Data type
    GLenum m_type = 0;

    // Components for a single attribute
    size_t m_componentsPerElement = 0;
    // Size of single component in bytes
    size_t m_componentSize = 0;
    // Number of elements stored in the buffer
    size_t m_elementCount = 0;
};