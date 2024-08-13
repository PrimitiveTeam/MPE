#pragma once

#include "Character.h"

#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Pipeline/VertexBuffer.h"
#include "MPE/Renderer/Shaders/Shader.h"

#include <string>
#include <map>

#include <glm/glm.hpp>
#include <freetype/freetype.h>

namespace MPE
{
class MPE_API TextRenderer
{
  public:
    ~TextRenderer() = default;

    virtual void RenderText(const std::string& text, float x, float y, float scale, const glm::vec4& color) = 0;

    bool GetPixelAlign() const { return m_PixelAlign; }
    void SetPixelAlign(bool pixelAlign) { m_PixelAlign = pixelAlign; }

    float GetFontSize() const { return m_FontSize; }
    virtual void SetFontSize(float fontSize) = 0;

    virtual void UpdateProjection(float screenWidth, float screenHeight) = 0;

  protected:
    virtual void InitializeFont() = 0;
    virtual void UnInitializeFont() = 0;
    virtual void LoadCharacters() = 0;

  protected:
    std::string m_FontPath;
    std::string m_ShaderPath;
    REF<Shader> m_Shader;
    FT_Library m_FT;
    FT_Face m_Face;
    REF<VertexArray> m_VAO;
    REF<VertexBuffer> m_VBO;
    std::map<char, Character> m_Characters;
    OrthographicCamera* m_MainCamera;

    // Parameters
    // Font Size
    float m_FontSize = 48.0f;
    // Pixel Perfect
    bool m_PixelAlign = false;
};
}
