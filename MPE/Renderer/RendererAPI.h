#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/RenderSettings.h"

#include <glm/glm.hpp>

namespace MPE
{
class MPE_API RendererAPI
{
  public:
    enum class API
    {
        None = 0,
        OpenGL = 1
        // Direct3D
        // Vulcan
    };

    virtual void Init() = 0;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

    virtual void SetClearColor(const glm::vec4 &color) = 0;
    virtual void Clear() = 0;

    virtual void DrawIndexed(const REF<VertexArray> &vertexArray) = 0;
    virtual void DrawLines(const REF<VertexArray> &vertexArray, uint32_t vertexCount) = 0;

    virtual RenderSettings *GetSettings() = 0;

    inline static API GetGraphicsAPI() { return GRAPHICS_API; }

  private:
    static API GRAPHICS_API;
};
}