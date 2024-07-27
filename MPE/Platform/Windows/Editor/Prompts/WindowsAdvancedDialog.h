#include "MPE/Editor/Prompts/AdvancedDialog.h"
#include "MPE/MPEPCH.h"
#include "MPE/MPEPLAT.h"

namespace MPE
{
class WindowsAdvancedDialog : public AdvancedDialog
{
  public:
    WindowsAdvancedDialog(const std::string &title, const std::string &message, const std::vector<DialogOption> &options)
        : AdvancedDialog(title, message, options)
    {
    }

    virtual DialogResponse show() override;

  private:
    static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};
}