#pragma once

#include "MPE/Events/Event.h"

namespace MPE
{
class MPE_API GraphicsSettingsChangedEvent : public Event
{
  public:
    GraphicsSettingsChangedEvent(std::string name, int32_t value);

    inline std::string GetSettingName() const { return Name; }
    inline int32_t GetSettingValue() const { return Value; }

    std::string ToString() const override;

    EVENT_CLASS_TYPE(GraphicsSettingsChanged)
    EVENT_CLASS_CATEGORY(EventCategoryGraphics)

  private:
    std::string Name;
    int32_t Value;
};

}