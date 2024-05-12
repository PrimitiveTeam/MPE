#pragma once

#include "MPE/Events/Event.h"

namespace MPE
{
    // Create a function called event
    class MPE_API FunctionCalledEvent : public Event
    {
    private:
        std::string FunctionName;

    public:
        // FunctionCalledEvent(std::string functionName)
        //     : FunctionName(functionName) {}
        FunctionCalledEvent(std::string functionName);

        inline std::string GetFunctionName() const { return FunctionName; }

        // std::string ToString() const override
        // {
        //     std::stringstream ss;
        //     ss << "FunctionCalledEvent: " << FunctionName;
        //     return ss.str();
        // }
        std::string ToString() const override;

        EVENT_CLASS_TYPE(FunctionCalled)
        EVENT_CLASS_CATEGORY(EventCategoryFunctions)
    };
}