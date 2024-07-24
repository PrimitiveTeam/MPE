#include "EventGraphics.h"
#include "MPE/MPEPCH.h"

#include <sstream>

namespace MPE
{
// GraphicsSettingsChangedEvent
GraphicsSettingsChangedEvent::GraphicsSettingsChangedEvent(std::string name, int32_t value) : Name(name), Value(value) {}

std::string GraphicsSettingsChangedEvent::ToString() const
{
    std::stringstream ss;
    ss << "GraphicsSettingsChangedEvent: " << Name << ", " << Value;
    return ss.str();
}

}