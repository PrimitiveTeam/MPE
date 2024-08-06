#include "EventKey.h"
#include "MPE/MPEPCH.h"

#include "MPE/Input/KeyState.h"

#include <sstream>

namespace MPE
{
// KeyEvent
KeyEvent::KeyEvent(int keycode) : KeyCode(keycode) {}

// KeyPressedEvent
KeyPressedEvent::KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), RepeatCount(repeatCount)
{
    MPE::KeyState::SetKeyPressed(keycode, true);
}

std::string KeyPressedEvent::ToString() const
{
    std::stringstream ss;
    ss << "KeyPressedEvent: " << KeyCode << " (" << RepeatCount << " repeats)";
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
    ss << "KeyReleasedEvent: " << KeyCode;
    return ss.str();
}

// KeyTypedEvent
KeyTypedEvent::KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

std::string KeyTypedEvent::ToString() const
{
    std::stringstream ss;
    ss << "KeyTypedEvent: " << KeyCode;
    return ss.str();
}
}
