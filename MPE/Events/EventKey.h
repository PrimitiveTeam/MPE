#pragma once

#include "MPE/Events/Event.h"

namespace MPE
{
    class MPE_API KeyEvent : public Event
    {
    protected:
        KeyEvent(int keycode);
        int KeyCode;

    public:
        inline int GetKeyCode() const { return KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    };

    class MPE_API KeyPressedEvent : public KeyEvent
    {
    private:
        int RepeatCount;

    public:
        KeyPressedEvent(int keycode, int repeatCount);

        inline int GetRepeatCount() const { return RepeatCount; }

        std::string ToString() const override;

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class MPE_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode);

        std::string ToString() const override;

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class MPE_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int keycode);

        std::string ToString() const override;

        EVENT_CLASS_TYPE(KeyTyped)
    };
}
