#include "MPE/Core/_PTRS.h"
#include "MPEPCH.h"
#include "MPEPLAT.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
std::string getCallerFunctionName()
{
    void *array[2];
    size_t size = backtrace(array, 2);
    if (size < 2) return "Unknown";

    char **strings = backtrace_symbols(array, size);
    if (!strings) return "Unknown";

    std::string caller = strings[1];
    free(strings);

    // Demangle the function name
    size_t begin = caller.find('(');
    size_t end = caller.find('+', begin);
    if (begin != std::string::npos && end != std::string::npos)
    {
        std::string func_name = caller.substr(begin + 1, end - begin - 1);
        int status;
        char *demangled = abi::__cxa_demangle(func_name.c_str(), 0, 0, &status);
        if (status == 0 && demangled)
        {
            std::string demangled_name = demangled;
            free(demangled);
            return demangled_name;
        }
        return func_name;
    }

    return "Unknown";
}
}