#include "_PTRS.h"
#include "MPEPCH.h"
#include "MPEPLAT.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
void ReferenceTracker::addReference(const std::string &type, const std::string &tag)
{
    std::lock_guard<std::mutex> lock(mutex_);
    references_[type + "::" + tag]++;
    totalReferences_[type]++;
}

void ReferenceTracker::removeReference(const std::string &type, const std::string &tag)
{
    std::lock_guard<std::mutex> lock(mutex_);
    references_[type + "::" + tag]--;
    totalReferences_[type]--;
    if (references_[type + "::" + tag] == 0)
    {
        references_.erase(type + "::" + tag);
    }
    if (totalReferences_[type] == 0)
    {
        totalReferences_.erase(type);
    }
}

void ReferenceTracker::displayReferences() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    std::cout << "Current References:" << std::endl;
    for (const auto &ref : references_)
    {
        if (ref.first.find("SCOPE") != std::string::npos)
        {
            std::cout << "SCOPE - " << ref.first << ": " << ref.second << std::endl;
        }
        else if (ref.first.find("REF") != std::string::npos)
        {
            std::cout << "REF - " << ref.first << ": " << ref.second << std::endl;
        }
        else
        {
            std::cout << ref.first << ": " << ref.second << std::endl;
        }
    }

    std::cout << "Total References by Type:" << std::endl;
    int totalScopeReferences = 0;
    int totalRefReferences = 0;
    for (const auto &totalRef : totalReferences_)
    {
        if (totalRef.first.find("SCOPE") != std::string::npos)
        {
            totalScopeReferences += totalRef.second;
        }
        else if (totalRef.first.find("REF") != std::string::npos)
        {
            totalRefReferences += totalRef.second;
        }
        else
        {
            std::cout << totalRef.first << ": " << totalRef.second << std::endl;
        }
    }

    std::cout << "SCOPE: " << totalScopeReferences << std::endl;
    std::cout << "REF: " << totalRefReferences << std::endl;
}

std::vector<std::string> ReferenceTracker::GetReferences() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<std::string> refs;
    for (const auto &ref : references_)
    {
        refs.push_back(ref.first);
    }
    return refs;
}

std::vector<std::string> ReferenceTracker::GetScopeReferences() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<std::string> refs;
    for (const auto &ref : references_)
    {
        if (ref.first.find("SCOPE") != std::string::npos)
        {
            refs.push_back(ref.first);
        }
    }
    return refs;
}

size_t ReferenceTracker::GetTotalReferences() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    size_t total = 0;
    for (const auto &ref : references_)
    {
        total += ref.second;
    }
    return total;
}

std::string getCallerFunctionName()
{
#ifdef MPE_PLATFORM_WINDOWS
    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();
    CONTEXT context;
    RtlCaptureContext(&context);

    STACKFRAME64 stackFrame;
    ZeroMemory(&stackFrame, sizeof(STACKFRAME64));

    DWORD machineType = IMAGE_FILE_MACHINE_AMD64;
    stackFrame.AddrPC.Offset = context.Rip;
    stackFrame.AddrPC.Mode = AddrModeFlat;
    stackFrame.AddrFrame.Offset = context.Rbp;
    stackFrame.AddrFrame.Mode = AddrModeFlat;
    stackFrame.AddrStack.Offset = context.Rsp;
    stackFrame.AddrStack.Mode = AddrModeFlat;

    SymInitialize(process, NULL, TRUE);
    for (int i = 0; i < 3; ++i)
    {
        if (!StackWalk64(machineType, process, thread, &stackFrame, &context, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL))
        {
            return "Unknown";
        }
    }

    DWORD64 address = stackFrame.AddrPC.Offset;
    if (address == 0)
    {
        return "Unknown";
    }

    char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
    PSYMBOL_INFO symbol = (PSYMBOL_INFO) buffer;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = MAX_SYM_NAME;

    DWORD64 displacement;
    if (SymFromAddr(process, address, &displacement, symbol))
    {
        return symbol->Name;
    }
    return "Unknown";
#elif MPE_PLATFORM_LINUX || MPE_PLATFORM_MACOS
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
#endif
}
}