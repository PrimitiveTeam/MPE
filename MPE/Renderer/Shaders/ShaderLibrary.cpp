#include "ShaderLibrary.h"
#include "MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/Renderer/RendererAPI.h"
#include "ShaderUtils.h"

namespace MPE
{
void ShaderLibrary::Add(const std::string &name, const REF<Shader> &shader)
{
    MPE_CORE_ASSERT(!Exists(name), "SHADER ALREADY EXISTS");
#if MPE_PLATFORM_LINUX
    SHADERS.insert(std::make_pair(name, shader));
#else
    SHADERS[name] = shader;
#endif
}

void ShaderLibrary::Add(const REF<Shader> &shader)
{
    auto &name = shader->GetName();
    Add(name, shader);
}

REF<Shader> ShaderLibrary::Load(const std::string &filepath, bool useEditorResource)
{
    std::string path = filepath;
    if (useEditorResource)
    {
        path = ShaderUtils::ParseEditorResourcePath(filepath);
    }

    auto shader = Shader::Create(path);
    Add(shader);
    return shader;
}

REF<Shader> ShaderLibrary::Load(const std::string &name, const std::string &filepath, bool useEditorResource)
{
    std::string path = filepath;
    if (useEditorResource)
    {
        path = ShaderUtils::ParseEditorResourcePath(filepath);
    }

    auto shader = Shader::Create(path);
    Add(name, shader);
    return shader;
}

REF<Shader> ShaderLibrary::Get(const std::string &name)
{
    MPE_CORE_ASSERT(Exists(name), "SHADER NOT FOUND");
#if MPE_PLATFORM_LINUX
    auto it = SHADERS.find(name);
    MPE_CORE_ASSERT(it != SHADERS.end(), "SHADER NOT FOUND");
    return it->second;
#else
    return SHADERS[name];
#endif
}

bool ShaderLibrary::Exists(const std::string &name) const
{
    return SHADERS.find(name) != SHADERS.end();
}

std::string GetGraphicsAPI()
{
    return RendererAPI::APIToString(RendererAPI::GetGraphicsAPI());
}
}