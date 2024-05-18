#include "MPE/Errors/Error.h"
#include "MPE/MPEPCH.h"
#include "MPE/MPEPLAT.h"

#include <string>

namespace MPE
{
const void Error::showExceptionDialog(const std::exception &e)
{
    std::string errorMessage = "An unhandled exception occurred: ";
    errorMessage += e.what();
    std::cout << errorMessage << std::endl;
}
}