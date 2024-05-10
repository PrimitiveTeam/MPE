#include "EventFunction.h"
#include "MPE/MPEPCH.h"

#include <sstream>

namespace MPE
{
    // FunctionCalledEvent
    FunctionCalledEvent::FunctionCalledEvent(std::string functionName)
        : FunctionName(functionName) {}

    std::string FunctionCalledEvent::ToString() const
    {
        std::stringstream ss;
        ss << "FunctionCalledEvent: " << FunctionName;
        return ss.str();
    }
}