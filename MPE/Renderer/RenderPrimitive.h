#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/RendererAPI.h"

#ifdef MPE_OPENGL
#    include "Platform/OpenGL/OpenGLRendererAPI.h"
#endif
#ifdef MPE_OPENGLES
#    include "Platform/OpenGLES/OpenGLESRendererAPI.h"
#endif

namespace MPE
{
class MPE_API RenderPrimitive
{
  public:
    inline static void Init()
    {
        if (!m_isApiSelected) throw std::runtime_error("Graphics API not selected.");

        m_rendererApi->Init();
    }
    inline static void Shutdown()
    {
        if (!m_isApiSelected) throw std::runtime_error("Graphics API not selected.");

        m_rendererApi->Shutdown();
    }

    inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { m_rendererApi->SetViewport(x, y, width, height); }

    inline static void SetClearColor(const glm::vec4 &color) { m_rendererApi->SetClearColor(color); }
    inline static void Clear() { m_rendererApi->Clear(); }

    inline static void DrawIndexed(const REF<VertexArray> &vertexArray) { m_rendererApi->DrawIndexed(vertexArray); }
    inline static void DrawLines(const REF<VertexArray> &vertexArray, uint32_t vertexCount) { m_rendererApi->DrawLines(vertexArray, vertexCount); }

    inline static RenderSettings *GetSettings() { return m_rendererApi->GetSettings(); }
    inline static void SetGraphicsAPI(RendererAPI::API api)
    {
        if (m_isApiSelected) throw std::runtime_error("Graphics API already selected.");

        switch (api)
        {
            case RendererAPI::API::OpenGL:
#ifdef MPE_OPENGL
                m_rendererApi = new OpenGLRendererAPI();
                break;
#else
                throw std::runtime_error("OpenGL not supported.");
#endif
            case RendererAPI::API::OpenGLES:
#ifdef MPE_OPENGLES
                m_rendererApi = new OpenGLESRendererAPI();
                break;
#else
                throw std::runtime_error("OpenGLES not supported.");
#endif
            default:
                throw std::runtime_error("Invalid graphics API.");
        }

        m_rendererApi->SetGraphicsAPI(api);
        m_isApiSelected = true;
    }

  private:
    static RendererAPI *m_rendererApi;
    inline static bool m_isApiSelected = false;
};
}