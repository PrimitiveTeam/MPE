#include "Texture2D.h"
#include "MPEPCH.h"

#include "MPE/Renderer/Renderer.h"
#include "MPE/Platform/OpenGL/Textures/OpenGLTexture2D.h"
#include "MPE/Platform/OpenGLES/Textures/OpenGLESTexture2D.h"

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
            return NEWREF<OpenGLTexture2D>(filepath);

        case RendererAPI::API::OpenGLES:
            return NEWREF<OpenGLESTexture2D>(filepath);

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
            return NEWREF<OpenGLTexture2D>(width, height);

        case RendererAPI::API::OpenGLES:
            return NEWREF<OpenGLESTexture2D>(width, height);

        default:
            MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
            return nullptr;
    }
}
}