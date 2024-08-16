#pragma once

#include "MPE/Events/Event.h"

namespace MPE
{
// WindowMovedEvent
class MPE_API WindowMovedEvent : public Event
{
  public:
    WindowMovedEvent(int x, int y);

    inline int GetX() const { return m_x; }
    inline int GetY() const { return m_y; }

    std::string ToString() const override;

    EVENT_CLASS_TYPE(WindowMoved)
    EVENT_CLASS_CATEGORY(EventCategoryApp)

  private:
    int m_x, m_y;
};

class MPE_API WindowResizeEvent : public Event
{
  public:
    WindowResizeEvent(unsigned int width, unsigned int height);

    inline unsigned int GetWidth() const { return m_width; }
    inline unsigned int GetHeight() const { return m_height; }

    std::string ToString() const override;

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApp)

  private:
    unsigned int m_width, m_height;
};

class MPE_API WindowCloseEvent : public Event
{
  public:
    WindowCloseEvent();

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
};

class MPE_API AppTickEvent : public Event
{
  public:
    AppTickEvent();

    EVENT_CLASS_TYPE(AppTick)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
};

class MPE_API AppUpdateEvent : public Event
{
  public:
    AppUpdateEvent();

    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
};

class MPE_API AppRenderEvent : public Event
{
  public:
    AppRenderEvent();

    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
};

}