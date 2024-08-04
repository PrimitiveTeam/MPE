#include "IndexBuffer.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Renderer/Renderer.h"
#include "MPE/Log/GlobalLog.h"

#ifdef MPE_OPENGL
#    include "Platform/OpenGL/Pipeline/OpenGLIndexBuffer.h"
#endif
#ifdef MPE_OPENGLES
#    include "Platform/OpenGLES/Pipeline/OpenGLESIndexBuffer.h"
#endif

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
#ifdef MPE_OPENGL
            return NEWREF<OpenGLIndexBuffer>(indices, count);
#else
            MPE_CORE_ASSERT(false, "OPENGL IS NOT SUPPORTED.");
            return nullptr;
#endif

        case RendererAPI::API::OpenGLES:
#ifdef MPE_OPENGLES
            return NEWREF<OpenGLESIndexBuffer>(indices, count);
#else
            MPE_CORE_ASSERT(false, "OPENGLES IS NOT SUPPORTED.");
            return nullptr;
#endif
        default:
            MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
            return nullptr;
    }
}
}