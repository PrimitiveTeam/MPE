#include "Texture2D.h"
#include "MPEPCH.h"

#include "MPE/Renderer/Renderer.h"

#ifdef MPE_OPENGL
#    include "Platform/OpenGL/Textures/OpenGLTexture2D.h"
#endif
#ifdef MPE_OPENGLES
#    include "Platform/OpenGLES/Textures/OpenGLESTexture2D.h"
#endif

namespace MPE
{
REF<Texture2D> Texture2D::Create(const std::string &filepath)
{
    switch (Renderer::GetCurrentGraphicsAPI())
    {
        case RendererAPI::API::None:
            MPE_CORE_ASSERT(false, "NO GRAPHICAL API IS CURRENTLY NOT SUPPORTED.");
            return nullptr;

        case RendererAPI::API::OpenGL:
#ifdef MPE_OPENGL
            return NEWREF<OpenGLTexture2D>(filepath);
#else
            MPE_CORE_ASSERT(false, "OPENGL IS NOT SUPPORTED.");
            return nullptr;
#endif
        case RendererAPI::API::OpenGLES:

#ifdef MPE_OPENGLES
            return NEWREF<OpenGLESTexture2D>(filepath);
#else
            MPE_CORE_ASSERT(false, "OPENGLES IS NOT SUPPORTED.");
            return nullptr;
#endif
        default:
            MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
            return nullptr;
    }
}
REF<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
{
    switch (Renderer::GetCurrentGraphicsAPI())
    {
        case RendererAPI::API::None:
            MPE_CORE_ASSERT(false, "NO GRAPHICAL API IS CURRENTLY NOT SUPPORTED.");
            return nullptr;

        case RendererAPI::API::OpenGL:
#ifdef MPE_OPENGL
            return NEWREF<OpenGLTexture2D>(width, height);
#else
            MPE_CORE_ASSERT(false, "OPENGL IS NOT SUPPORTED.");
            return nullptr;
#endif

        case RendererAPI::API::OpenGLES:
#ifdef MPE_OPENGLES
            return NEWREF<OpenGLESTexture2D>(width, height);
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