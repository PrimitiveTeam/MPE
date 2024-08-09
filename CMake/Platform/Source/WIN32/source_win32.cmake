file(
  GLOB_RECURSE
  MPE_WIN32_CPP

  # /Platform/Windows/App
  "${PROJECT_SOURCE_DIR}/Platform/Windows/App/WindowsWindow.cpp"
  "${PROJECT_SOURCE_DIR}/Platform/Windows/App/WindowMonitors.cpp"

  # /Platform/Windows/Core
  "${PROJECT_SOURCE_DIR}/Platform/Windows/Core/_PTRS.cpp"

  # /Platform/Windows/Editor/Prompts
  "${PROJECT_SOURCE_DIR}/Platform/Windows/Editor/Prompts/WindowSimpleDialog.cpp"

  # /Platform/Windows/Errors
  "${PROJECT_SOURCE_DIR}/Platform/Windows/Errors/Error.cpp"

  # /Platform/Windows/Input
  "${PROJECT_SOURCE_DIR}/Platform/Windows/Input/WindowsInput.cpp"
)

file(
  GLOB_RECURSE
  MPE_WIN32_H

  # /Platform/Windows/App
  "${PROJECT_SOURCE_DIR}/Platform/Windows/App/WindowsWindow.h"
  "${PROJECT_SOURCE_DIR}/Platform/Windows/App/WindowMonitors.h"

  # /Platform/Windows/Input
  "${PROJECT_SOURCE_DIR}/Platform/Windows/Input/WindowsInput.h"
)

# ADD MPE WIN32 SOURCE FILES
list(APPEND MPE_CPP ${MPE_WIN32_CPP})

list(APPEND MPE_H ${MPE_WIN32_H})

# PRINT MPE WIN32 SOURCE FILES
if(${VERBOSE})
  message("
MPE WIN32 SOURCE AND HEADER FILES

WIN32 SOURCE FILES:\n")

  foreach(MPE_WIN32_CPP_FILE ${MPE_WIN32_CPP})
    message("${MPE_WIN32_CPP_FILE}")
  endforeach()

  message("
WIN32 HEADER FILES:\n")

  foreach(MPE_WIN32_H_FILE ${MPE_WIN32_H})
    message("${MPE_WIN32_H_FILE}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()