#pragma once
#include <unordered_map>

namespace MPE
{
class KeyState
{
  public:
    static void SetKeyPressed(int keycode, bool pressed);
    static bool IsKeyPressed(int keycode);
    static bool WasKeyPressed(int keycode);
    static bool IsKeyJustPressed(int keycode);

    static void Update();

  private:
    static std::unordered_map<int, bool> m_CurrentState;
    static std::unordered_map<int, bool> m_PreviousState;
};
}
