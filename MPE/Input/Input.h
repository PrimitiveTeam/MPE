#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Input/KeyCodes.h"
#include "MPE/Input/MouseButtonCodes.h"
#include "MPE/Input/KeyState.h"

namespace MPE
{
class MPE_API Input
{
  public:
    inline static bool IsKeyPressed(int keycode) { return m_inputInstance->IsKeyPressedImpl(keycode); }
    inline static bool IsKeyJustPressed(int keycode) { return KeyState::IsKeyJustPressed(keycode); }
    inline static bool IsMouseButtonPressed(int button) { return m_inputInstance->IsMouseButtonPressedImpl(button); }
    inline static std::pair<float, float> GetMousePosition() { return m_inputInstance->GetMousePositionImpl(); }
    inline static float GetMouseX() { return m_inputInstance->GetMouseXImpl(); }
    inline static float GetMouseY() { return m_inputInstance->GetMouseYImpl(); }

    static void Update() { KeyState::Update(); }

  private:
    static REF<Input> m_inputInstance;

  protected:
    virtual bool IsKeyPressedImpl(int keycode) = 0;
    virtual bool IsMouseButtonPressedImpl(int button) = 0;
    virtual std::pair<float, float> GetMousePositionImpl() = 0;
    virtual float GetMouseXImpl() = 0;
    virtual float GetMouseYImpl() = 0;
};
}