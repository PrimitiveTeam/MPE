#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace MPE
{
OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) : m_Size(size)
{
// TODO: Add a check for OpenGL version using compiler defines.
#ifdef MPE_PLATFORM_OSX
    glGenBuffers(1, &SYS_Renderer_ID);
#else
    glCreateBuffers(1, &SYS_Renderer_ID);
#endif
    glBindBuffer(GL_ARRAY_BUFFER, SYS_Renderer_ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &SYS_Renderer_ID);
}

void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, SYS_Renderer_ID);
}

void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}