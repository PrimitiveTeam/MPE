#include "ShaderLibrary.h"
#include "MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"
#include "MPE/Renderer/RendererAPI.h"
#include "ShaderUtils.h"

namespace MPE
{
REF<std::unordered_map<std::string, REF<Shader>>> ShaderLibrary::m_shaders = nullptr;

void ShaderLibrary::Init()
{
    MPE_CORE_INFO("SHADER LIBRARY INITIALIZED");
    m_shaders = NEWREF<std::unordered_map<std::string, REF<Shader>>>();
}

void ShaderLibrary::Shutdown()
{
    m_shaders->clear();
    MPE_CORE_INFO("SHADER LIBRARY SHUTDOWN");
}

void ShaderLibrary::Add(const std::string &name, const REF<Shader> &shader)
{
    MPE_CORE_ASSERT(!Exists(name), "SHADER ALREADY EXISTS");
#if MPE_PLATFORM_LINUX
    m_shaders->insert(std::make_pair(name, shader));
#else
    (*m_shaders)[name] = shader;
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
    auto it = m_shaders->find(name);
    MPE_CORE_ASSERT(it != m_shaders.end(), "SHADER NOT FOUND");
    return it->second;
#else
    return (*m_shaders)[name];
#endif
}

bool ShaderLibrary::Exists(const std::string &name)
{
    return m_shaders->find(name) != m_shaders->end();
}

std::string GetGraphicsAPI()
{
    return RendererAPI::APIToString(RendererAPI::GetGraphicsAPI());
}
}