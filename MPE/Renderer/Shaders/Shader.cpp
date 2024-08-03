#include "Shader.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Renderer/Renderer.h"
#include "MPE/Log/GlobalLog.h"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"
#include "Platform/OpenGLES/Shaders/OpenGLESShader.h"

namespace MPE
{
REF<Shader> Shader::Create(const std::string &filepath, bool useEditorResource)
{
    switch (Renderer::GetCurrentGraphicsAPI())
    {
        case RendererAPI::API::None:
            MPE_CORE_ASSERT(false, "NO GRAPHICAL API IS CURRENTLY NOT SUPPORTED.");
            return nullptr;

        case RendererAPI::API::OpenGL:
            return NEWREF<OpenGLShader>(filepath, useEditorResource);

        case RendererAPI::API::OpenGLES:
            return NEWREF<OpenGLESShader>(filepath, useEditorResource);

        default:
            MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
            return nullptr;
    }
}
REF<Shader> Shader::Create(const std::string &name, const std::string &vertexSource, const std::string &fragmentSource)
{
    switch (Renderer::GetCurrentGraphicsAPI())
    {
        case RendererAPI::API::None:
            MPE_CORE_ASSERT(false, "NO GRAPHICAL API IS CURRENTLY NOT SUPPORTED.");
            return nullptr;

        case RendererAPI::API::OpenGL:
            return NEWREF<OpenGLShader>(name, vertexSource, fragmentSource);

        case RendererAPI::API::OpenGLES:
            return NEWREF<OpenGLESShader>(name, vertexSource, fragmentSource);

        default:
            MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
            return nullptr;
    }
}
// This will be used to load shaders for specific Graphics APIs. This will be called when we are loading shaders from the editor resources.
// Usuall path will be:
// Data/Shaders/ColoredTexture.glsl
// We need to take Data/Shaders/ and add the specific API path to it.
// For example for OpenGL it will be:
// Data/Shaders/OpenGL/ColoredTexture.glsl
std::string Shader::ParseEditorResourcePath(const std::string &filepath)
{
    std::string path = filepath;
    // Look for Shaders/ in the path
    size_t pos = path.find("Shaders/");
    if (pos == std::string::npos)
    {
        MPE_CORE_ERROR("INVALID SHADER PATH: {0}", path);
        MPE_CORE_ASSERT(0, "INVALID SHADER PATH");
    }
    // Add the specific API path to the path
    auto selectedApi = MPE::RendererAPI::GetGraphicsAPI();

    switch (selectedApi)
    {
        case MPE::RendererAPI::API::OpenGL:
            path.insert(pos + 8, "OpenGL/");
            break;
        case MPE::RendererAPI::API::OpenGLES:
            path.insert(pos + 8, "OpenGLES/");
            break;
        default:
            MPE_CORE_ERROR("INVALID GRAPHICS API: {0}", MPE::RendererAPI::APIToString(selectedApi));
            MPE_CORE_ASSERT(0, "INVALID GRAPHICS API");
            break;
    }

    return path;
}
}