#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/RendererAPI.h"

namespace MPE
{
class MPE_API RenderPrimitive
{
  public:
    inline static void Init() { SYS_API->Init(); }

    inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { SYS_API->SetViewport(x, y, width, height); }

    inline static void SetClearColor(const glm::vec4 &color) { SYS_API->SetClearColor(color); }
    inline static void Clear() { SYS_API->Clear(); }

    inline static void DrawIndexed(const REF<VertexArray> &vertexArray) { SYS_API->DrawIndexed(vertexArray); }
    inline static void DrawLines(const REF<VertexArray> &vertexArray, uint32_t vertexCount) { SYS_API->DrawLines(vertexArray, vertexCount); }

    inline static RenderSettings *GetSettings() { return SYS_API->GetSettings(); }

  private:
    static RendererAPI *SYS_API;
};
}