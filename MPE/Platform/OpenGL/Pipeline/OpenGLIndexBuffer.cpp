#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace MPE
{
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : SYS_COUNT(count)
{
    glCreateBuffers(1, &SYS_Renderer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SYS_Renderer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &SYS_Renderer_ID);
}

void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SYS_Renderer_ID);
}

void OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}