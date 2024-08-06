#include "ShaderUtils.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Renderer/RendererAPI.h"
#include "MPE/Log/GlobalLog.h"

#ifdef MPE_OPENGL
#    include "Platform/OpenGL/Shaders/OpenGLShader.h"
#endif
#ifdef MPE_OPENGLES
#    include "Platform/OpenGLES/Shaders/OpenGLESShader.h"
#endif

namespace MPE
{
namespace ShaderUtils
{
// This will be used to load shaders for specific Graphics APIs. This will be called when we are loading shaders from the editor resources.
// Usuall path will be:
// Data/Shaders/ColoredTexture.glsl
// We need to take Data/Shaders/ and add the specific API path to it.
// For example for OpenGL it will be:
// Data/Shaders/OpenGL/ColoredTexture.glsl
std::string ParseEditorResourcePath(const std::string &filepath)
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
}