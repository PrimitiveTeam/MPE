#include "SimpleDialog.h"

namespace MPE
{
SimpleDialog::SimpleDialog() : m_title(""), m_message(""), m_type(DialogType::OK) {}

SimpleDialog::SimpleDialog(const std::string &title, const std::string &message, DialogType type) : m_title(title), m_message(message), m_type(type) {}

SimpleDialog::~SimpleDialog() {}
}