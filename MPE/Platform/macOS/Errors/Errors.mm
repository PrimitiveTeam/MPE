#include "MPE/Errors/Error.h"
#include "MPE/MPEPCH.h"
#include "MPE/MPEPLAT.h"
#include "MPE/Log/GlobalLog.h"

namespace MPE
{
const void Error::showExceptionDialog(const std::exception &e)
{
    MPE_CORE_WARN("TEST");

    std::string errorMessage = "An unhandled exception occurred: ";
    errorMessage += e.what();

    @autoreleasepool
    {
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:@"Unhandled Exception"];
        [alert setInformativeText:[NSString stringWithUTF8String:errorMessage.c_str()]];
        [alert addButtonWithTitle:@"OK"];
        [alert setAlertStyle:NSAlertStyleCritical];
        [alert runModal];
    }
}
}