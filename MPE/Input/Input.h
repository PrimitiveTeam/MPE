#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Input/KeyCodes.h"
#include "MPE/Input/MouseButtonCodes.h"

namespace MPE
{
class MPE_API Input
{
  private:
    static REF<Input> SYS_Input_Instance;

  protected:
    virtual bool IsKeyPressedImpl(int keycode) = 0;
    virtual bool IsMouseButtonPressedImpl(int button) = 0;
    virtual std::pair<float, float> GetMousePositionImpl() = 0;
    virtual float GetMouseXImpl() = 0;
    virtual float GetMouseYImpl() = 0;

  public:
    inline static bool IsKeyPressed(int keycode) { return SYS_Input_Instance->IsKeyPressedImpl(keycode); }
    inline static bool IsMouseButtonPressed(int button) { return SYS_Input_Instance->IsMouseButtonPressedImpl(button); }
    inline static std::pair<float, float> GetMousePosition() { return SYS_Input_Instance->GetMousePositionImpl(); }
    inline static float GetMouseX() { return SYS_Input_Instance->GetMouseXImpl(); }
    inline static float GetMouseY() { return SYS_Input_Instance->GetMouseYImpl(); }
};
}