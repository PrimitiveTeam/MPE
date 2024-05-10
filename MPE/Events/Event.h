#pragma once

#include "MPE/Core/_CORE.h"

#include <functional>
#include <string>

namespace MPE
{
    enum class EventType
    {
        None = 0,
        // WINDOW EVENTS:
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoves,
        // APP EVENTS:
        AppTick,
        AppUpdate,
        AppRender,
        // KEY EVENTS:
        KeyPressed,
        KeyReleased,
        KeyTyped,
        // MOUSE EVENTS:
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled

    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApp = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType GetStaticType() { return EventType::type; }                \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

    class MPE_API Event
    {
    private:
        friend class EventDispatcher;

    public:
        bool SYS_Handled = false;
        virtual EventType GetEventType() const = 0;
        // Only for debugging
        virtual const char *GetName() const = 0;
        //
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

    class EventDispatcher
    {
        template <typename T>
        using EventFn = std::function<bool(T &)>;

    public:
        EventDispatcher(Event &event)
            : SYS_Event(event) {}

        template <typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (SYS_Event.GetEventType() == T::GetStaticType())
            {
                SYS_Event.SYS_Handled = func(*(T *)&SYS_Event);
                return true;
            }
            return false;
        }

    private:
        Event &SYS_Event;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e)
    {
        return os << e.ToString();
    }
}