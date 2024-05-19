#include "EventMouse.h"
#include "MPE/MPEPCH.h"

#include <sstream>

namespace MPE
{
// MouseMovedEvent
MouseMovedEvent::MouseMovedEvent(float x, float y) : MouseX(x), MouseY(y) {}

std::string MouseMovedEvent::ToString() const
{
    std::stringstream ss;
    ss << "MouseMovedEvent: " << MouseX << ", " << MouseY;
    return ss.str();
}

// MouseScrolledEvent
MouseScrolledEvent::MouseScrolledEvent(float xoffset, float yoffset) : XOffset(xoffset), YOffset(yoffset) {}
std::string MouseScrolledEvent::ToString() const
{
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
    return ss.str();
}

// MouseButtonEvent
MouseButtonEvent::MouseButtonEvent(int button) : Button(button) {}

// MouseButtonPressedEvent
MouseButtonPressedEvent::MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

std::string MouseButtonPressedEvent::ToString() const
{
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << Button;
    return ss.str();
}

// MouseButtonReleasedEvent
MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

std::string MouseButtonReleasedEvent::ToString() const
{
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << Button;
    return ss.str();
}

}