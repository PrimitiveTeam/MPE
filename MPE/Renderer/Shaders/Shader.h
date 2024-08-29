#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
class MPE_API Shader
{
  public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    // DEBUG
    virtual void Unbind() const = 0;
    // DEBUG

    virtual void SetInt1(const std::string &name, int value) = 0;
    virtual void SetInt2(const std::string &name, int values[2]) = 0;
    virtual void SetInt3(const std::string &name, int values[3]) = 0;
    virtual void SetInt4(const std::string &name, int values[4]) = 0;
    virtual void SetFloat1(const std::string &name, float value) = 0;
    virtual void SetFloat2(const std::string &name, const glm::vec2 &vector2) = 0;
    virtual void SetFloat3(const std::string &name, const glm::vec3 &vector3) = 0;
    virtual void SetFloat4(const std::string &name, const glm::vec4 &vector4) = 0;
    virtual void SetMat3(const std::string &name, const glm::mat3 &matrix) = 0;
    virtual void SetMat4(const std::string &name, const glm::mat4 &matrix) = 0;

    virtual const std::string &GetName() const = 0;

    static REF<Shader> Create(const std::string &filepath, bool useEditorResource = false);
    static REF<Shader> Create(const std::string &name, const std::string &vertexSource, const std::string &fragmentSource);

    // virtual void InjectUniformBuffer
};
}