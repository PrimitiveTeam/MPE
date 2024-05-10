#pragma once

#include "MPE/Events/Event.h"

namespace MPE
{
    class MPE_API WindowResizeEvent : public Event
    {
    private:
        unsigned int Width, Height;

    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : Width(width), Height(height) {}

        inline unsigned int GetWidth() const { return Width; }
        inline unsigned int GetHeight() const { return Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << Width << ", " << Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApp)
    };

    class MPE_API WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApp)
    };

    class MPE_API AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApp)
    };

    class MPE_API AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApp)
    };

    class MPE_API AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApp)
    };

}