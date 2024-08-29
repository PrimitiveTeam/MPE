
#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

#include <string>

namespace MPE
{
class MPE_EDITOR_API SimpleDialog
{
  public:
    enum class DialogType
    {
        OK,
        OK_CANCEL,
        YES_NO,
        YES_NO_CANCEL
    };

    struct DialogResponse
    {
        enum
        {
            OK = 1,
            CANCEL = 2,
            YES = 3,
            NO = 4
        };

        int m_response;

        DialogResponse(int response) : m_response(response) {}

        operator bool() const { return m_response == OK || m_response == YES; }

        bool operator==(int value) const { return m_response == value; }
        bool operator!=(int value) const { return m_response != value; }

        bool isOK() const { return m_response == OK; }
        bool isCancel() const { return m_response == CANCEL; }
        bool isYes() const { return m_response == YES; }
        bool isNo() const { return m_response == NO; }
    };

  public:
    SimpleDialog();
    SimpleDialog(const std::string &title, const std::string &message, DialogType type = DialogType::OK);

    ~SimpleDialog();

    // MPE/Platform/x/Editor/Prompts/xSimpleDialog.cpp
    DialogResponse Show();

  private:
    std::string m_title;
    std::string m_message;
    DialogType m_type;
};
}