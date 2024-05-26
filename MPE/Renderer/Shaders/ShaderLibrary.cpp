#include "ShaderLibrary.h"
#include "MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
void ShaderLibrary::Add(const std::string &name, const REF<Shader> &shader)
{
    MPE_CORE_ASSERT(!Exists(name), "SHADER ALREADY EXISTS");
    SHADERS[name] = shader;
}

void ShaderLibrary::Add(const REF<Shader> &shader)
{
    auto &name = shader->GetName();
    Add(name, shader);
}

REF<Shader> ShaderLibrary::Load(const std::string &filepath)
{
    auto shader = Shader::Create(filepath);
    Add(shader);
    return shader;
}

REF<Shader> ShaderLibrary::Load(const std::string &name, const std::string &filepath)
{
    auto shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
}

REF<Shader> ShaderLibrary::Get(const std::string &name)
{
    MPE_CORE_ASSERT(Exists(name), "SHADER NOT FOUND");
    return SHADERS[name];
}

bool ShaderLibrary::Exists(const std::string &name) const
{
    return SHADERS.find(name) != SHADERS.end();
}
}