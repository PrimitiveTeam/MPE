#pragma once

#include "AdvancedDialog.h"
#include <memory>

namespace MPE
{
std::unique_ptr<AdvancedDialog> CreateAdvancedDialog(const std::string &title, const std::string &message,
                                                     const std::vector<AdvancedDialog::DialogOption> &options);
}
