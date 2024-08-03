file(
  GLOB_RECURSE
  MPE_Linux_CPP

  # /Platform/Linux/App
  "${PROJECT_SOURCE_DIR/Platform/Linux/App/LinuxWindow.cpp"
  "${PROJECT_SOURCE_DIR/Platform/Linux/App/LinuxMonitors.cpp"

  # /Platform/Linux/Core
  "${PROJECT_SOURCE_DIR/Platform/Linux/Core/_PTRS.cpp"

  # /Platform/Linux/Errors
  "${PROJECT_SOURCE_DIR/Platform/Linux/Errors/Error.cpp"

  # /Platform/Linux/Input
  "${PROJECT_SOURCE_DIR/Platform/Linux/Input/LinuxInput.cpp"
)

file(
  GLOB_RECURSE
  MPE_Linux_H

  # /Platform/Linux/App
  "${PROJECT_SOURCE_DIR/Platform/Linux/App/LinuxWindow.h"
  "${PROJECT_SOURCE_DIR/Platform/Linux/App/LinuxMonitors.h"

  # /Platform/Linux/Input
  "${PROJECT_SOURCE_DIR/Platform/Linux/Input/LinuxInput.h"
)

# ADD MPE Linux SOURCE FILES
list(APPEND MPE_CPP ${MPE_Linux_CPP})

list(APPEND MPE_H ${MPE_Linux_H})

# PRINT MPE Linux SOURCE FILES
if(${VERBOSE})
  message("
MPE LINUX SOURCE AND HEADER FILES

LINUX SOURCE FILES:\n")

  foreach(MPE_LINUX_CPP_FILE ${MPE_LINUX_CPP})
    message("${MPE_LINUX_CPP_FILE}")
  endforeach()

  message("
LINUX HEADER FILES:\n")

  foreach(MPE_LINUX_H_FILE ${MPE_LINUX_H})
    message("${MPE_LINUX_H_FILE}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()