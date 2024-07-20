#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Shaders/Shader.h"

namespace MPE
{
class MPE_API ShaderLibrary
{
  public:
    void Add(const std::string &name, const REF<Shader> &shader);
    void Add(const REF<Shader> &shader);

    REF<Shader> Load(const std::string &filepath);
    REF<Shader> Load(const std::string &name, const std::string &filepath);
    REF<Shader> Get(const std::string &name);

    bool Exists(const std::string &name) const;

  private:
    std::unordered_map<std::string, REF<Shader>> SHADERS;
};
}