#include "IndexBuffer.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Renderer/Renderer.h"
#include "MPE/Platform/OpenGL/Pipeline/OpenGLIndexBuffer.h"
#include "MPE/Platform/OpenGLES/Pipeline/OpenGLESIndexBuffer.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
REF<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count)
{
    switch (Renderer::GetCurrentGraphicsAPI())
    {
        case RendererAPI::API::None:
            MPE_CORE_ASSERT(false, "NO GRAPHICAL API IS CURRENTLY NOT SUPPORTED.");
            return nullptr;

        case RendererAPI::API::OpenGL:
            return NEWREF<OpenGLIndexBuffer>(indices, count);

        case RendererAPI::API::OpenGLES:
            return NEWREF<OpenGLESIndexBuffer>(indices, count);

        default:
            MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
            return nullptr;
    }
}
}