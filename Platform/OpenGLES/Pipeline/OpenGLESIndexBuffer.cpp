#include "OpenGLESIndexBuffer.h"

#include <GLES3/gl31.h>

namespace MPE
{
OpenGLESIndexBuffer::OpenGLESIndexBuffer(uint32_t *indices, uint32_t count) : SYS_COUNT(count)
{
    glGenBuffers(1, &SYS_Renderer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SYS_Renderer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLESIndexBuffer::~OpenGLESIndexBuffer()
{
    glDeleteBuffers(1, &SYS_Renderer_ID);
}

void OpenGLESIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SYS_Renderer_ID);
}

void OpenGLESIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}