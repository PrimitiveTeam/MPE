#pragma once

#include "MPE/Renderer/Text/TextRenderer.h"
#include "MPE/Events/EventApp.h"

#include "MPE/Vendor/GLM/GLM.h"

typedef unsigned int GLuint;

namespace MPE
{
class MPE_API OpenGLTextRenderer : public TextRenderer
{
  public:
    OpenGLTextRenderer(const std::string& shaderPath, const std::string& fontPath, int fontSize);
    ~OpenGLTextRenderer();

    void OnEvent(Event& e);

    virtual void RenderText(const std::string& text, float x, float y, float scale, const glm::vec4& color) override;

    virtual void SetFontSize(float fontSize) override;

    virtual void UpdateProjection(float screenWidth, float screenHeight) override;

  private:
    virtual void InitializeFont() override;
    virtual void UnInitializeFont() override;
    virtual void LoadCharacters() override;

    bool OnWindowResize(WindowResizeEvent& e);

  private:
};
}
