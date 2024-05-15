#include "Error.h"
#include "MPE/MPEPCH.h"

namespace MPE
{
Error::Error() : code_(0), message_("Unknown error"), severity_(Severity::Error), category_(Category::None) {}

Error::Error(int code, const std::string &message, Severity severity, Category category)
    : code_(code), message_(message), severity_(severity), category_(category)
{
}

void Error::std_log() const
{
    std::cout << "Error " << code_ << ": " << message_ << " [Severity: " << static_cast<int>(severity_)
              << ", Category: " << std::bitset<4>(static_cast<int>(category_)) << "]" << std::endl;
}

std::string Error::get_verbose_log() const
{
    return "Error " + std::to_string(code_) + ": " + message_ + " [Severity: " + std::to_string(static_cast<int>(severity_)) +
           ", Category: " + (std::bitset<4>(static_cast<int>(category_))).to_string() + "]";
}

const char *Error::what() const noexcept
{
    return message_.c_str();
}

const Error &Error::get(int code)
{
    static std::map<int, Error> errors;
    return errors[code];
}

}