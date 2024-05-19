#include "IndexBuffer.h"
#include "MPE/MPEPCH.h"

#include "MPE/Renderer/Renderer.h"
#include "MPE/Platform/OpenGL/Pipeline/OpenGLIndexBuffer.h"
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
        }
        MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
        return nullptr;
    }
}