#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Shaders/Shader.h"

namespace MPE
{
class MPE_API ShaderLibrary
{
  public:
    static void Init();
    static void Shutdown();

    static void Add(const std::string &name, const REF<Shader> &shader);
    static void Add(const REF<Shader> &shader);

    static REF<Shader> Load(const std::string &filepath, bool useEditorResource = false);
    static REF<Shader> Load(const std::string &name, const std::string &filepath, bool useEditorResource = false);

    static REF<Shader> AddOrLoadIfExists(const std::string &filepath, bool useEditorResource = false);
    static REF<Shader> AddOrLoadIfExists(const std::string &name, const std::string &filepath, bool useEditorResource = false);

    static REF<Shader> Get(const std::string &name);

    static bool Exists(const std::string &name);

  private:
    ShaderLibrary() = default;
    ~ShaderLibrary() = default;

  private:
    static REF<std::unordered_map<std::string, REF<Shader>>> m_shaders;
};
}