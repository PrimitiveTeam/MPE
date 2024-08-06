#include "MPE/Core/_PTRS.h"
#include "MPEPCH.h"
#include "MPEPLAT.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
std::string getCallerFunctionName()
{
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
}
}