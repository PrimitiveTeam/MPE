#pragma once

#include "MPE/Events/Event.h"

namespace MPE
{
class MPE_API MouseMovedEvent : public Event
{
  public:
    MouseMovedEvent(float x, float y);

    inline float GetX() const { return MouseX; }
    inline float GetY() const { return MouseY; }

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float MouseX, MouseY;
};

class MPE_API MouseScrolledEvent : public Event
{
  public:
    MouseScrolledEvent(float xoffset, float yoffset);
    inline float GetXOffset() const { return XOffset; }
    inline float GetYOffset() const { return YOffset; }

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float XOffset, YOffset;
};

class MPE_API MouseButtonEvent : public Event
{
  public:
    inline int GetMouseButton() const { return Button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  protected:
    MouseButtonEvent(int button);

    int Button;
};

class MPE_API MouseButtonPressedEvent : public MouseButtonEvent
{
  public:
    MouseButtonPressedEvent(int button);

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MPE_API MouseButtonReleasedEvent : public MouseButtonEvent
{
  public:
    MouseButtonReleasedEvent(int button);

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseButtonReleased)
};
}