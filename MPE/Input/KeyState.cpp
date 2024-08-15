#include "KeyState.h"

namespace MPE
{
std::unordered_map<int, bool> KeyState::m_currentState;
std::unordered_map<int, bool> KeyState::m_previousState;

void KeyState::SetKeyPressed(int keycode, bool pressed)
{
#if MPE_PLATFORM_LINUX
    auto it = m_currentState.find(keycode);
    if (it != m_currentState.end())
    {
        it->second = pressed;
    }
    else
    {
        m_currentState.emplace(keycode, pressed);
    }
#else
    m_currentState[keycode] = pressed;
#endif
}

bool KeyState::IsKeyPressed(int keycode)
{
#if MPE_PLATFORM_LINUX
    auto it = m_currentState.find(keycode);
    if (it != m_currentState.end()) return it->second;
    return false;
#else
    return m_currentState[keycode];
#endif
}

bool KeyState::WasKeyPressed(int keycode)
{
#if MPE_PLATFORM_LINUX
    auto it = m_previousState.find(keycode);
    if (it != m_previousState.end()) return it->second;
    return false;
#else
    return m_previousState[keycode];
#endif
}

bool KeyState::IsKeyJustPressed(int keycode)
{
#if MPE_PLATFORM_LINUX
    auto currentIt = m_currentState.find(keycode);
    auto previousIt = m_previousState.find(keycode);
    bool currentPressed = currentIt != m_currentState.end() && currentIt->second;
    bool previousPressed = previousIt != m_previousState.end() && previousIt->second;
    return currentPressed && !previousPressed;
#else
    return m_currentState[keycode] && !m_previousState[keycode];
#endif
}

void KeyState::Update()
{
    m_previousState = m_currentState;
}
}
