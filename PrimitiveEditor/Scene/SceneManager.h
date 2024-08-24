#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/Scene/Scene.h"

#include <stack>

namespace MPE
{
class MPE_API SceneManager
{
  public:
    SceneManager();
    ~SceneManager() = default;

    void PushScene(REF<Scene> scene);

    void PopScene();

    void OnUpdate(Time deltaTime);

    void OnRender();

    void OnImGuiRender();

    void OnEvent(Event& event);

  private:
    std::stack<REF<Scene>> m_scenes;
};
}