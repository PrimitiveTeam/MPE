#include "MPE/Errors/Error.h"
#include "MPE/MPEPCH.h"

namespace MPE
{
const void Error::showExceptionDialog(const std::exception &e)
{
    std::string errorMessage = "An unhandled exception occurred: ";
    errorMessage += e.what();
    MessageBoxA(NULL, errorMessage.c_str(), "Unhandled Exception", MB_ICONERROR | MB_OK);
}
}