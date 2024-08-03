#include "VertexBuffer.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Renderer/Renderer.h"
#include "Platform/OpenGL/Pipeline/OpenGLVertexBuffer.h"
#include "Platform/OpenGLES/Pipeline/OpenGLESVertexBuffer.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
REF<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size)
{
    switch (Renderer::GetCurrentGraphicsAPI())
    {
        case RendererAPI::API::None:
            MPE_CORE_ASSERT(false, "NO GRAPHICAL API IS CURRENTLY NOT SUPPORTED.");
            return nullptr;

        case RendererAPI::API::OpenGL:
            return NEWREF<OpenGLVertexBuffer>(vertices, size);

        case RendererAPI::API::OpenGLES:
            return NEWREF<OpenGLESVertexBuffer>(vertices, size);

        default:
            MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
            return nullptr;
    }
}
}