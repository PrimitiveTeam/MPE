#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Log/GlobalLog.h"

#include <functional>
#include <string>

namespace MPE
{
enum class MPE_API EventType
{
    None = 0,
    // WINDOW EVENTS
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    // APP EVENTS
    AppTick,
    AppUpdate,
    AppRender,
    // GRAPHICS EVENTS
    GraphicsSettingsChanged,
    // KEY EVENTS
    KeyPressed,
    KeyReleased,
    KeyTyped,
    // MOUSE EVENTS
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
    // FUNCTION EVENTS
    FunctionCalled

};

enum MPE_API EventCategory
{
    None = 0,
    EventCategoryApp = BIT(0),
    EventCategoryGraphics = BIT(1),
    EventCategoryInput = BIT(2),
    EventCategoryKeyboard = BIT(3),
    EventCategoryMouse = BIT(4),
    EventCategoryMouseButton = BIT(5),
    EventCategoryFunctions = BIT(6)
};

#define EVENT_CLASS_TYPE(type)                      \
    static EventType GetStaticType()                \
    {                                               \
        return EventType::type;                     \
    }                                               \
    virtual EventType GetEventType() const override \
    {                                               \
        return GetStaticType();                     \
    }                                               \
    virtual const char *GetName() const override    \
    {                                               \
        return #type;                               \
    }

#define EVENT_CLASS_CATEGORY(category)            \
    virtual int GetCategoryFlags() const override \
    {                                             \
        return category;                          \
    }

class MPE_API Event
{
  public:
    bool SYS_Handled = false;
    virtual EventType GetEventType() const = 0;
    // Only for debugging
    virtual const char *GetName() const = 0;
    //
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

  private:
    friend class EventDispatcher;
};

class MPE_API EventDispatcher
{
    template <typename T>
    using EventFn = std::function<bool(T &)>;

  public:
    EventDispatcher(Event &event) : SYS_Event(event) {}

    template <typename T>
    bool Dispatch(EventFn<T> func)
    {
        if (SYS_Event.GetEventType() == T::GetStaticType())
        {
            SYS_Event.SYS_Handled = func(*(T *) &SYS_Event);
            MPE_DEBUG_TRACE("Event: {0}", SYS_Event.ToString());
            return true;
        }
        return false;
    }

  private:
    Event &SYS_Event;
};

MPE_API inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
    return os << e.ToString();
}
}