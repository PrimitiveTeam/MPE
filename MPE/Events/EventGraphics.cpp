#include "EventGraphics.h"
#include "MPE/MPEPCH.h"

#include <sstream>

namespace MPE
{
// GraphicsSettingsChangedEvent
GraphicsSettingsChangedEvent::GraphicsSettingsChangedEvent(std::string name, int32_t value) : m_name(name), m_value(value) {}

std::string GraphicsSettingsChangedEvent::ToString() const
{
    std::stringstream ss;
    ss << "GraphicsSettingsChangedEvent: " << m_name << ", " << m_value;
    return ss.str();
}

}