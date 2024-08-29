#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Shaders/Shader.h"

#if MPE_PLATFORM_LINUX
typedef int GLint;
#else
#    include <glad/glad.h>
#endif
#include "MPE/Vendor/GLM/GLM.h"

// TEMP
typedef unsigned int GLenum;
// TEMP

namespace MPE
{
class MPE_API OpenGLShader : public Shader
{
  public:
    OpenGLShader(const std::string &filepath, bool useEditorResource = false);
    OpenGLShader(const std::string &name, const std::string &vertexSource, const std::string &fragmentSource);
    virtual ~OpenGLShader();

    virtual void Bind() const override;
    // DEBUG
    virtual void Unbind() const override;
    // DEBUG

    virtual void SetInt1(const std::string &name, int value) override;
    virtual void SetInt2(const std::string &name, int values[2]) override;
    virtual void SetInt3(const std::string &name, int values[3]) override;
    virtual void SetInt4(const std::string &name, int values[4]) override;
    virtual void SetFloat1(const std::string &name, float value) override;
    virtual void SetFloat2(const std::string &name, const glm::vec2 &vector2) override;
    virtual void SetFloat3(const std::string &name, const glm::vec3 &vector3) override;
    virtual void SetFloat4(const std::string &name, const glm::vec4 &vector4) override;
    virtual void SetMat3(const std::string &name, const glm::mat3 &matrix) override;
    virtual void SetMat4(const std::string &name, const glm::mat4 &matrix) override;

    virtual const std::string &GetName() const override { return m_name; };

    void InjectUniformInt1(const std::string &name, int value);
    void InjectUniformInt2(const std::string &name, int values[2]);
    void InjectUniformInt3(const std::string &name, int values[3]);
    void InjectUniformInt4(const std::string &name, int values[4]);

    void InjectUniformFloat1(const std::string &name, float value);
    void InjectUniformFloat2(const std::string &name, const glm::vec2 &vector2);
    void InjectUniformFloat3(const std::string &name, const glm::vec3 &vector3);
    void InjectUniformFloat4(const std::string &name, const glm::vec4 &vector4);

    void InjectUniformMat3(const std::string &name, const glm::mat3 &matrix);
    void InjectUniformMat4(const std::string &name, const glm::mat4 &matrix);

  private:
    void CheckIfBound(const std::string &name) const;
    GLint CheckUniform(const std::string &name) const;

  private:
    uint32_t m_shaderId;
    std::string m_name;

    std::string ValidateFile(const std::string &filepath);
    std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);
    void Compile(std::unordered_map<GLenum, std::string> &shaders);
};
}