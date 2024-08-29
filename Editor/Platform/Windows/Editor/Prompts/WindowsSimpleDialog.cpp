#include "Editor/Editor/Prompts/SimpleDialog.h"
#include "MPE/MPEPCH.h"
#include "MPE/MPEPLAT.h"

namespace MPE
{
MPE::SimpleDialog::DialogResponse MPE::SimpleDialog::Show()
{
    // Implement platform-specific dialog creation and showing logic for Windows
    UINT type;
    switch (m_type)
    {
        case DialogType::OK:
            type = MB_OK;
            break;
        case DialogType::OK_CANCEL:
            type = MB_OKCANCEL;
            break;
        case DialogType::YES_NO:
            type = MB_YESNO;
            break;
        case DialogType::YES_NO_CANCEL:
            type = MB_YESNOCANCEL;
            break;
        default:
            type = MB_OK;
    }

    int response = MessageBox(NULL, m_message.c_str(), m_title.c_str(), type);

    switch (response)
    {
        case IDOK:
            return DialogResponse(DialogResponse::OK);
        case IDCANCEL:
            return DialogResponse(DialogResponse::CANCEL);
        case IDYES:
            return DialogResponse(DialogResponse::YES);
        case IDNO:
            return DialogResponse(DialogResponse::NO);
        default:
            return DialogResponse(DialogResponse::CANCEL);
    }
}
}
