#ifdef MPE_PLATFORM_WINDOWS
#    include <Windows.h>
#endif

#ifdef MPE_PLATFORM_LINUX or MPE_PLATFORM_OSX
#    include <unistd.h>
#endif

#ifdef MPE_PLATFORM_OSX
#    include <Cocoa/Cocoa.h>
#endif