#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/RenderPrimitive.h"
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Renderer/Shaders/Shader.h"
#include "MPE/Renderer/RenderInformation/RenderInfo.h"

namespace MPE
{
class MPE_API Renderer
{
  public:
    static void Init();
    static void OnWindowResize(uint32_t width, uint32_t height);

    // OBJECT, LIGHTING, ENVIRONMENT
    static void BeginScene(OrthographicCamera &camera);
    static void EndScene();
    static void Submit(const REF<Shader> &shader, const REF<VertexArray> &vertexArray, const glm::mat4 &transform = glm::mat4(1.0f));

    inline static RendererAPI::API GetCurrentGraphicsAPI() { return RendererAPI::GetGraphicsAPI(); }

    // Update the FPS and MS
    inline static void UpdateFPS_MS(Time deltaTime) { SYS_WINDOW_FPS_MS->Update(deltaTime); }
    // Get the FPSMS struct
    inline static WINDOW_FPS_MS GetFPS_MS() { return *SYS_WINDOW_FPS_MS; }

  private:
    struct SceneData
    {
        glm::mat4 PROJECTION_VIEW_MATRIX;
    };

    static SceneData *SYS_SCENE;

    static REF<WINDOW_FPS_MS> SYS_WINDOW_FPS_MS;
};
}