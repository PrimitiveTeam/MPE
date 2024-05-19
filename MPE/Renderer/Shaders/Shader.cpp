#include "Shader.h"
#include "MPE/MPEPCH.h"

#include "MPE/Renderer/Renderer.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/Platform/OpenGL/Shaders/OpenGLShader.h"

namespace MPE
{
REF<Shader> Shader::Create(const std::string &filepath)
{
    switch (Renderer::GetCurrentGraphicsAPI())
    {
        case RendererAPI::API::None:
            MPE_CORE_ASSERT(false, "NO GRAPHICAL API IS CURRENTLY NOT SUPPORTED.");
            return nullptr;

        case RendererAPI::API::OpenGL:
            return NEWREF<OpenGLShader>(filepath);
    }
    MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
    return nullptr;
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
    }
    MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
    return nullptr;
}
}