#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/RendererAPI.h"
#include "MPE/Platform/OpenGL/OpenGLSettings.h"

namespace MPE
{
class MPE_API OpenGLRendererAPI : public RendererAPI
{
  public:
    virtual void Init() override;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

    virtual void SetClearColor(const glm::vec4 &color) override;
    virtual void Clear() override;

    virtual void DrawIndexed(const REF<VertexArray> &vertexArray) override;

    virtual RenderSettings *GetSettings() override;

  private:
    OpenGLSettings *SYS_Settings;
};
}