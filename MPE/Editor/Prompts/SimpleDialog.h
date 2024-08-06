
#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

#include <string>

namespace MPE
{
class SimpleDialog
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

        int response;

        DialogResponse(int response) : response(response) {}

        operator bool() const { return response == OK || response == YES; }

        bool operator==(int value) const { return response == value; }
        bool operator!=(int value) const { return response != value; }

        bool isOK() const { return response == OK; }
        bool isCancel() const { return response == CANCEL; }
        bool isYes() const { return response == YES; }
        bool isNo() const { return response == NO; }
    };

  public:
    SimpleDialog();
    SimpleDialog(const std::string &title, const std::string &message, DialogType type = DialogType::OK);

    ~SimpleDialog();

    // MPE/Platform/x/Editor/Prompts/xSimpleDialog.cpp
    DialogResponse Show();

  private:
    std::string m_Title;
    std::string m_Message;
    DialogType m_Type;
};
}