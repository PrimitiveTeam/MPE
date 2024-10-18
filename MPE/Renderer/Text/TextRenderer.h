#pragma once

#include "Character.h"

// #include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Pipeline/VertexBuffer.h"
#include "MPE/Renderer/Shaders/Shader.h"

#include <string>
#include <map>

#include "MPE/Vendor/GLM/GLM.h"
#include <freetype/freetype.h>

namespace MPE
{
class MPE_API TextRenderer
{
  public:
    ~TextRenderer() = default;

    virtual void RenderText(const std::string& text, float x, float y, float scale, const glm::vec4& color) = 0;

    bool GetPixelAlign() const { return m_pixelAlign; }
    void SetPixelAlign(bool pixelAlign) { m_pixelAlign = pixelAlign; }

    float GetFontSize() const { return m_fontSize; }
    virtual void SetFontSize(float fontSize) = 0;

    virtual void UpdateProjection(float screenWidth, float screenHeight) = 0;

    virtual void RenderAllASCII(float x, float y, float scale, const glm::vec4& color);

  protected:
    virtual void InitializeFont() = 0;
    virtual void UnInitializeFont() = 0;
    virtual void LoadCharacters() = 0;

  protected:
    std::string m_fontPath;
    std::string m_shaderPath;
    REF<Shader> m_shader;
    FT_Library m_FT;
    FT_Face m_Face;
    REF<VertexArray> m_VAO;
    REF<VertexBuffer> m_VBO;
    std::map<char, Character> m_characters;
    // OrthographicCamera* m_mainCamera;

    // Parameters
    // Font Size
    float m_fontSize = 48.0f;
    // Pixel Perfect
    bool m_pixelAlign = false;
};
}
