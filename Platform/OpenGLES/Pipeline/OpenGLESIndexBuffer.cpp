#include "OpenGLESIndexBuffer.h"

#include <GLES3/gl31.h>

namespace MPE
{
OpenGLESIndexBuffer::OpenGLESIndexBuffer(uint32_t *indices, uint32_t count) : m_count(count)
{
    glGenBuffers(1, &m_indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLESIndexBuffer::~OpenGLESIndexBuffer()
{
    glDeleteBuffers(1, &m_indexBufferId);
}

void OpenGLESIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
}

void OpenGLESIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}