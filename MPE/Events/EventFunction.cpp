#include "EventFunction.h"
#include "MPE/MPEPCH.h"

#include <sstream>

namespace MPE
{
// FunctionCalledEvent
FunctionCalledEvent::FunctionCalledEvent(std::string functionName) : m_functionName(functionName) {}

std::string FunctionCalledEvent::ToString() const
{
    std::stringstream ss;
    ss << "FunctionCalledEvent: " << m_functionName;
    return ss.str();
}
}