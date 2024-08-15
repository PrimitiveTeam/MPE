#pragma once

#include "MPE/Events/Event.h"

namespace MPE
{
class MPE_API MouseMovedEvent : public Event
{
  public:
    MouseMovedEvent(float x, float y);

    inline float GetX() const { return m_mouseX; }
    inline float GetY() const { return m_mouseY; }

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float m_mouseX, m_mouseY;
};

class MPE_API MouseScrolledEvent : public Event
{
  public:
    MouseScrolledEvent(float xoffset, float yoffset);
    inline float GetXOffset() const { return m_xOffset; }
    inline float GetYOffset() const { return m_yOffset; }

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float m_xOffset, m_yOffset;
};

class MPE_API MouseButtonEvent : public Event
{
  public:
    inline int GetMouseButton() const { return m_button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  protected:
    MouseButtonEvent(int button);

    int m_button;
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