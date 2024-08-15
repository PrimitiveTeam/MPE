#pragma once

#include "MPE/Events/Event.h"

namespace MPE
{
// Create a function called event
class MPE_API FunctionCalledEvent : public Event
{
  public:
    FunctionCalledEvent(std::string functionName);

    inline std::string GetFunctionName() const { return m_functionName; }

    std::string ToString() const override;

    EVENT_CLASS_TYPE(FunctionCalled)
    EVENT_CLASS_CATEGORY(EventCategoryFunctions)

  private:
    std::string m_functionName;
};
}