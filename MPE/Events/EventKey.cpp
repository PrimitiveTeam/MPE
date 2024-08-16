#include "EventKey.h"
#include "MPE/MPEPCH.h"

#include "MPE/Input/KeyState.h"

#include <sstream>

namespace MPE
{
// KeyEvent
KeyEvent::KeyEvent(int keycode) : m_keyCode(keycode) {}

// KeyPressedEvent
KeyPressedEvent::KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_repeatCount(repeatCount)
{
    MPE::KeyState::SetKeyPressed(keycode, true);
}

std::string KeyPressedEvent::ToString() const
{
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
    return ss.str();
}

// KeyReleasedEvent
KeyReleasedEvent::KeyReleasedEvent(int keycode) : KeyEvent(keycode)
{
    MPE::KeyState::SetKeyPressed(keycode, false);
}

std::string KeyReleasedEvent::ToString() const
{
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << m_keyCode;
    return ss.str();
}

// KeyTypedEvent
KeyTypedEvent::KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

std::string KeyTypedEvent::ToString() const
{
    std::stringstream ss;
    ss << "KeyTypedEvent: " << m_keyCode;
    return ss.str();
}
}
