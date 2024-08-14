#include "OpenGLESVertexBuffer.h"

#include "Platform/OpenGLES/Utilities/OpenGLESUtilities.h"

#include <GLES3/gl31.h>

namespace MPE
{
OpenGLESVertexBuffer::OpenGLESVertexBuffer(float* vertices, uint32_t size) : m_Size(size)
{
    // TODO: Add a check for OpenGLES version using compiler defines.
    glGenBuffers(1, &SYS_Renderer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, SYS_Renderer_ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLESVertexBuffer::OpenGLESVertexBuffer(uint32_t size) : m_Size(size)
{
    // TODO: Add a check for OpenGLES version using compiler defines.
    glGenBuffers(1, &SYS_Renderer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, SYS_Renderer_ID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

    glCheckError();
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

void OpenGLESVertexBuffer::SetData(const void* data, uint32_t size)
{
    // TODO: Add a way to check if already bound
    // glBindBuffer(GL_ARRAY_BUFFER, SYS_Renderer_ID);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    glBindBuffer(GL_ARRAY_BUFFER, SYS_Renderer_ID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

    glCheckError();
}
}