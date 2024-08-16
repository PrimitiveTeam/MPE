#include "OpenGLESVertexArray.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "Platform/OpenGLES/Utilities/OpenGLESUtilities.h"

#include <GLES3/gl31.h>

namespace MPE
{
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
        case MPE::ShaderDataType::None:
            MPE_CORE_ASSERT(false, "INVALID SHADER TYPE");
        case MPE::ShaderDataType::Bool:
            return GL_BOOL;
        case MPE::ShaderDataType::Int1:
            return GL_INT;
        case MPE::ShaderDataType::Int2:
            return GL_INT;
        case MPE::ShaderDataType::Int3:
            return GL_INT;
        case MPE::ShaderDataType::Int4:
            return GL_INT;
        case MPE::ShaderDataType::Vec1:
            return GL_FLOAT;
        case MPE::ShaderDataType::Vec2:
            return GL_FLOAT;
        case MPE::ShaderDataType::Vec3:
            return GL_FLOAT;
        case MPE::ShaderDataType::Vec4:
            return GL_FLOAT;
        case MPE::ShaderDataType::Mat3:
            return GL_FLOAT;
        case MPE::ShaderDataType::Mat4:
            return GL_FLOAT;
    }
    MPE_CORE_ASSERT(false, "UNKOWN SHADER DATA TYPE.");
    return 0;
}

OpenGLESVertexArray::OpenGLESVertexArray()
{
    glGenVertexArrays(1, &m_vertexArrayId);
}

OpenGLESVertexArray::~OpenGLESVertexArray()
{
    glDeleteVertexArrays(1, &m_vertexArrayId);
}

void OpenGLESVertexArray::Bind() const
{
    glBindVertexArray(m_vertexArrayId);
}

void OpenGLESVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGLESVertexArray::AddVertexBuffer(const REF<VertexBuffer> &vertexBuffer)
{
    MPE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VERTEX BUFFER HAS NO LAYOUT.");

    glBindVertexArray(m_vertexArrayId);
    vertexBuffer->Bind();

    uint32_t index = 0;
    const auto &layout = vertexBuffer->GetLayout();
    for (const auto &element : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.m_type), element.m_normalized ? GL_TRUE : GL_FALSE,
                              layout.GetStride(), (const void *) (intptr_t) element.m_offset);
        index++;

        glCheckError();
    }
    m_vertexBuffers.push_back(vertexBuffer);
}

void OpenGLESVertexArray::SetIndexBuffer(const REF<IndexBuffer> &indexBuffer)
{
    glBindVertexArray(m_vertexArrayId);
    indexBuffer->Bind();

    m_indexBuffer = indexBuffer;
    // m_indexBufferS.push_back(indexBuffer);
}
}