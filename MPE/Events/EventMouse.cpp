#include "EventMouse.h"
#include "MPE/MPEPCH.h"

#include <sstream>

namespace MPE
{
// MouseMovedEvent
MouseMovedEvent::MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

std::string MouseMovedEvent::ToString() const
{
    std::stringstream ss;
    ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
    return ss.str();
}

// MouseScrolledEvent
MouseScrolledEvent::MouseScrolledEvent(float xoffset, float yoffset) : m_xOffset(xoffset), m_yOffset(yoffset) {}
std::string MouseScrolledEvent::ToString() const
{
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
    return ss.str();
}

// MouseButtonEvent
MouseButtonEvent::MouseButtonEvent(int button) : m_button(button) {}

// MouseButtonPressedEvent
MouseButtonPressedEvent::MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

std::string MouseButtonPressedEvent::ToString() const
{
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << m_button;
    return ss.str();
}

// MouseButtonReleasedEvent
MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

std::string MouseButtonReleasedEvent::ToString() const
{
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << m_button;
    return ss.str();
}

}