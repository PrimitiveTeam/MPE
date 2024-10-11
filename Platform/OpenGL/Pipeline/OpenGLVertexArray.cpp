#include "OpenGLVertexArray.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "Platform/OpenGL/Utilities/OpenGLUtilities.h"

#include <glad/glad.h>

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

OpenGLVertexArray::OpenGLVertexArray()
{
#ifdef MPE_PLATFORM_OSX
    glGenVertexArrays(1, &m_vertexArrayId);
#else
    glCreateVertexArrays(1, &m_vertexArrayId);
#endif
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_vertexArrayId);
}

void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_vertexArrayId);
}

void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const REF<VertexBuffer> &vertexBuffer)
{
    MPE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VERTEX BUFFER HAS NO LAYOUT.");

    glBindVertexArray(m_vertexArrayId);
    vertexBuffer->Bind();

    uint32_t index = 0;
    const auto &layout = vertexBuffer->GetLayout();
    for (const auto &element : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type), element.normalized ? GL_TRUE : GL_FALSE,
                              layout.GetStride(), (const void *) (intptr_t) element.offset);
        index++;

        // #include <typeinfo>
        // MPE_TRACE("VERTEX BUFFER LAYOUT: {0}, {1}, {2}, {3}, {4}, {5}", element.title, typeid(ShaderDataTypeToOpenGLBaseType(element.type)).name(), element.size, element.offset, element.normalized, layout.GetStride());
        // MPE_TRACE("GL_FLOAT: {0}, Returned Value: {1}", GL_FLOAT, ShaderDataTypeToOpenGLBaseType(MPE::ShaderDataType::Vec3));

        glCheckError();
    }
    m_vertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const REF<IndexBuffer> &indexBuffer)
{
    glBindVertexArray(m_vertexArrayId);
    indexBuffer->Bind();

    m_indexBuffer = indexBuffer;
    // SYS_INDEXBUFFERS.push_back(indexBuffer);
}
}