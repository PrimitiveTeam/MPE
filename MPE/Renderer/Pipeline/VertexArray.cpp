#include "VertexArray.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Renderer/Renderer.h"
#include "Platform/OpenGL/Pipeline/OpenGLVertexArray.h"
#include "Platform/OpenGLES/Pipeline/OpenGLESVertexArray.h"
#include "MPE/Log/GlobalLog.h"

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
            return NEWREF<OpenGLVertexArray>();

        case RendererAPI::API::OpenGLES:
            return NEWREF<OpenGLESVertexArray>();

        default:
            MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
            return nullptr;
    }
}
}