#include "SimpleDialog.h"

namespace MPE
{
SimpleDialog::SimpleDialog() : m_Title(""), m_Message(""), m_Type(DialogType::OK) {}

SimpleDialog::SimpleDialog(const std::string &title, const std::string &message, DialogType type) : m_Title(title), m_Message(message), m_Type(type) {}

SimpleDialog::~SimpleDialog() {}
}