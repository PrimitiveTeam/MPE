#include "EventApp.h"
#include "MPE/MPEPCH.h"

#include <sstream>

namespace MPE
{
// WindowMovesEvent
WindowMovedEvent::WindowMovedEvent(int x, int y) : X(x), Y(y) {}

std::string WindowMovedEvent::ToString() const
{
    std::stringstream ss;
    ss << "WindowMovedEvent: " << X << ", " << Y;
    return ss.str();
}

// WindowResizeEvent
WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height) : Width(width), Height(height) {}

std::string WindowResizeEvent::ToString() const
{
    std::stringstream ss;
    ss << "WindowResizeEvent: " << Width << ", " << Height;
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