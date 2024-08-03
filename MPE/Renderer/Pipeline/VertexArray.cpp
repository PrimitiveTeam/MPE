#include "VertexArray.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Renderer/Renderer.h"
#include "MPE/Log/GlobalLog.h"

#ifdef MPE_OPENGL
#    include "Platform/OpenGL/Pipeline/OpenGLVertexArray.h"
#endif
#ifdef MPE_OPENGLES
#    include "Platform/OpenGLES/Pipeline/OpenGLESVertexArray.h"
#endif

namespace MPE
{
REF<VertexArray> VertexArray::Create()
{
    switch (Renderer::GetCurrentGraphicsAPI())
    {
        case RendererAPI::API::None:
            MPE_CORE_ASSERT(false, "NO GRAPHICAL API IS CURRENTLY NOT SUPPORTED.");
            return nullptr;

        case RendererAPI::API::OpenGL:
#ifdef MPE_OPENGL
            return NEWREF<OpenGLVertexArray>();
#else
            MPE_CORE_ASSERT(false, "OPENGL IS NOT SUPPORTED.");
            return nullptr;
#endif

        case RendererAPI::API::OpenGLES:
#ifdef MPE_OPENGLES
            return NEWREF<OpenGLESVertexArray>();
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