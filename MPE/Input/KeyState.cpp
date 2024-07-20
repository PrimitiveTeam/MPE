#include "KeyState.h"

namespace MPE
{
std::unordered_map<int, bool> KeyState::m_CurrentState;
std::unordered_map<int, bool> KeyState::m_PreviousState;

void KeyState::SetKeyPressed(int keycode, bool pressed)
{
#if MPE_PLATFORM_LINUX
    auto it = m_CurrentState.find(keycode);
    if (it != m_CurrentState.end())
    {
        it->second = pressed;
    }
    else
    {
        m_CurrentState.emplace(keycode, pressed);
    }
#else
    m_CurrentState[keycode] = pressed;
#endif
}

bool KeyState::IsKeyPressed(int keycode)
{
#if MPE_PLATFORM_LINUX
    auto it = m_CurrentState.find(keycode);
    if (it != m_CurrentState.end()) return it->second;
    return false;
#else
    return m_CurrentState[keycode];
#endif
}

bool KeyState::WasKeyPressed(int keycode)
{
#if MPE_PLATFORM_LINUX
    auto it = m_PreviousState.find(keycode);
    if (it != m_PreviousState.end()) return it->second;
    return false;
#else
    return m_PreviousState[keycode];
#endif
}

bool KeyState::IsKeyJustPressed(int keycode)
{
#if MPE_PLATFORM_LINUX
    auto currentIt = m_CurrentState.find(keycode);
    auto previousIt = m_PreviousState.find(keycode);
    bool currentPressed = currentIt != m_CurrentState.end() && currentIt->second;
    bool previousPressed = previousIt != m_PreviousState.end() && previousIt->second;
    return currentPressed && !previousPressed;
#else
    return m_CurrentState[keycode] && !m_PreviousState[keycode];
#endif
}

void KeyState::Update()
{
    m_PreviousState = m_CurrentState;
}
}
