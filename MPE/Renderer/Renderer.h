#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/RenderPrimitive.h"
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Renderer/Cameras/PerspectiveCamera.h"
#include "MPE/Renderer/Shaders/Shader.h"
#include "MPE/Renderer/Utilities/RenderInfo.h"

namespace MPE
{
class MPE_API Renderer
{
  public:
    static void Init();
    static void Shutdown();
    static void OnWindowResize(uint32_t width, uint32_t height);

    // OBJECT, LIGHTING, ENVIRONMENT
    static void BeginScene(OrthographicCamera &camera);
    static void BeginScene(PerspectiveCamera &camera);
    static void EndScene();
    static void Submit(const REF<Shader> &shader, const REF<VertexArray> &vertexArray, const glm::mat4 &transform = glm::mat4(1.0f));

    inline static RendererAPI::API GetCurrentGraphicsAPI() { return RendererAPI::GetGraphicsAPI(); }

    // Update the FPS and MS
    inline static void UpdateFpsMs(Time deltaTime) { m_windowFpsMs->Update(deltaTime); }
    // Get the FPSMS struct
    inline static WindowFpsMs GetFpsMs() { return *m_windowFpsMs; }

    // Set API
    inline static void SetGraphicsAPI(RendererAPI::API api) { RenderPrimitive::SetGraphicsAPI(api); }

  private:
    struct SceneData
    {
        glm::mat4 projectionViewMatrix;
    };

    static SceneData *m_scene;

    static REF<WindowFpsMs> m_windowFpsMs;
};
}