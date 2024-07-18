#include "KeyState.h"

namespace MPE
{
std::unordered_map<int, bool> KeyState::m_CurrentState;
std::unordered_map<int, bool> KeyState::m_PreviousState;

void KeyState::SetKeyPressed(int keycode, bool pressed)
{
    m_CurrentState[keycode] = pressed;
}

bool KeyState::IsKeyPressed(int keycode)
{
    return m_CurrentState[keycode];
}

bool KeyState::WasKeyPressed(int keycode)
{
    return m_PreviousState[keycode];
}

bool KeyState::IsKeyJustPressed(int keycode)
{
    return m_CurrentState[keycode] && !m_PreviousState[keycode];
}

void KeyState::Update()
{
    m_PreviousState = m_CurrentState;
}
}
