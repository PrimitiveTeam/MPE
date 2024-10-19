#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Textures/Texture2D.h"

namespace MPE
{
class MPE_API Renderer2D
{
  public:
    static void Init();
    static void Shutdown();

    static void BeginScene(const glm::mat4 &cameraProjectionViewMatrix);
    static void EndScene();

    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4 color);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4 color);
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const REF<Texture2D> texture, float tillingFactor = 1.0f);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const REF<Texture2D> texture, float tillingFactor = 1.0f);
};
}