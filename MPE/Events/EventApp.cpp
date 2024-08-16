#include "EventApp.h"
#include "MPE/MPEPCH.h"

#include <sstream>

namespace MPE
{
// WindowMovesEvent
WindowMovedEvent::WindowMovedEvent(int x, int y) : m_x(x), m_y(y) {}

std::string WindowMovedEvent::ToString() const
{
    std::stringstream ss;
    ss << "WindowMovedEvent: " << m_x << ", " << m_y;
    return ss.str();
}

// WindowResizeEvent
WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

std::string WindowResizeEvent::ToString() const
{
    std::stringstream ss;
    ss << "WindowResizeEvent: " << m_width << ", " << m_height;
    return ss.str();
}

// WindowCloseEvent
WindowCloseEvent::WindowCloseEvent() {}

// AppTickEvent
AppTickEvent::AppTickEvent() {}

// AppUpdateEvent
AppUpdateEvent::AppUpdateEvent() {}

// AppRenderEvent
AppRenderEvent::AppRenderEvent() {}
}