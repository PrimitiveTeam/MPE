#include "OpenGLVertexBuffer.h"

#include "Platform/OpenGL/Utilities/OpenGLUtilities.h"

#include <glad/glad.h>

namespace MPE
{
OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) : m_size(size)
{
// TODO: Add a check for OpenGL version using compiler defines.
#ifdef MPE_PLATFORM_OSX
    glGenBuffers(1, &m_vertexBufferId);
#else
    glCreateBuffers(1, &m_vertexBufferId);
#endif
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) : m_size(size)
{
// TODO: Add a check for OpenGL version using compiler defines.
#ifdef MPE_PLATFORM_OSX
    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
#else
    glCreateBuffers(1, &m_vertexBufferId);
    glNamedBufferStorage(m_vertexBufferId, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
#endif

    glCheckError();
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_vertexBufferId);
}

void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
}

void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
{
// TODO: Add a way to check if already bound
// glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
// glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
#ifdef MPE_PLATFORM_OSX
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
#else
    glNamedBufferSubData(m_vertexBufferId, 0, size, data);
#endif

    glCheckError();
}
}