#include "OpenGLESVertexBuffer.h"

#include <GLES3/gl31.h>

namespace MPE
{
OpenGLESVertexBuffer::OpenGLESVertexBuffer(float *vertices, uint32_t size) : m_Size(size)
{
    // TODO: Add a check for OpenGL version using compiler defines.
    glGenBuffers(1, &SYS_Renderer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, SYS_Renderer_ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLESVertexBuffer::~OpenGLESVertexBuffer()
{
    glDeleteBuffers(1, &SYS_Renderer_ID);
}

void OpenGLESVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, SYS_Renderer_ID);
}

void OpenGLESVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}