#ifdef MPE_PLATFORM_WINDOWS
#    include <Windows.h>
#    include <dbghelp.h>
#    pragma comment(lib, "Dbghelp.lib")
#endif

#ifdef MPE_PLATFORM_LINUX
#    include <unistd.h>
#    include <gtk/gtk.h>
#    include <execinfo.h>
#    include <cxxabi.h>
#endif

#ifdef MPE_PLATFORM_OSX
#    include <Cocoa/Cocoa.h>
#    include <unistd.h>
#    include <execinfo.h>
#    include <cxxabi.h>
#endif