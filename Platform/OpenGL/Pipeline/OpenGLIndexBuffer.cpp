#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace MPE
{
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : m_count(count)
{
#ifdef MPE_PLATFORM_OSX
    glGenBuffers(1, &m_indexBufferId);
#else
    glCreateBuffers(1, &m_indexBufferId);
#endif
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_indexBufferId);
}

void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
}

void OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}