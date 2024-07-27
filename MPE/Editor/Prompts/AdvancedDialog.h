#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

#include <string>
#include <vector>
#include <utility>

namespace MPE
{
class AdvancedDialog
{
  public:
    // Pair of option ID and option text
    using DialogOption = std::pair<int, std::string>;
    // Response will be the option ID
    using DialogResponse = int;

    AdvancedDialog(const std::string &title, const std::string &message, const std::vector<DialogOption> &options)
        : m_Title(title), m_Message(message), m_Options(options)
    {
    }

    virtual ~AdvancedDialog() {}

    // Pure virtual function for platform-specific implementation
    virtual DialogResponse show() = 0;

    static DialogResponse Show(const std::string &title, const std::string &message, const std::vector<DialogOption> &options);

  protected:
    std::string m_Title;
    std::string m_Message;
    std::vector<DialogOption> m_Options;
};
}