#include "MPE/Editor/Prompts/AdvancedDialogFactory.h"
#include "WindowsAdvancedDialog.h"

#include <memory>

namespace MPE
{
std::unique_ptr<AdvancedDialog> CreateAdvancedDialog(const std::string &title, const std::string &message,
                                                     const std::vector<AdvancedDialog::DialogOption> &options)
{
#ifdef _WIN32
    return std::make_unique<WindowsAdvancedDialog>(title, message, options);
#else
// Add other platform-specific implementations here
#    error "Platform not supported"
#endif
}

AdvancedDialog::DialogResponse AdvancedDialog::Show(const std::string &title, const std::string &message, const std::vector<DialogOption> &options)
{
    auto dialog = CreateAdvancedDialog(title, message, options);
    return dialog->show();
}
}
