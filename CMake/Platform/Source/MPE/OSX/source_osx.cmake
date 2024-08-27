file(
  GLOB_RECURSE
  MPE_macOS_CPP

  # /Platform/macOS/App
  "${PROJECT_SOURCE_DIR}/Platform/macOS/App/macOSWindow.cpp"
  "${PROJECT_SOURCE_DIR}/Platform/macOS/App/WindowMonitors.cpp"

  # /Platform/macOS/Core
  "${PROJECT_SOURCE_DIR}/Platform/macOS/Core/_PTRS.mm"

  # /Platform/macOS/Errors
  "${PROJECT_SOURCE_DIR}/Platform/macOS/Errors/Error.mm"

  # /Platform/macOS/Input
  "${PROJECT_SOURCE_DIR}/Platform/macOS/Input/macOSInput.cpp"
)

file(
  GLOB_RECURSE
  MPE_macOS_H

  # /Platform/macOS/App
  "${PROJECT_SOURCE_DIR}/Platform/macOS/App/macOSWindow.h"
  "${PROJECT_SOURCE_DIR}/Platform/macOS/App/WindowMonitors.h"

  # /Platform/macOS/Input
  "${PROJECT_SOURCE_DIR}/Platform/macOS/Input/macOSInput.h"
)

# ADD MPE macOS SOURCE FILES
list(APPEND MPE_CPP ${MPE_macOS_CPP})

list(APPEND MPE_H ${MPE_macOS_H})

# WHEN ANGLE DEPENDENCIES ARE ENABLED WE NEED TO PROVIDE macOSContext sources
if (MPE_ANGLE)
list(APPEND MPE_CPP "${PROJECT_SOURCE_DIR}/Platform/macOS/App/macOSContext.mm")
list(APPEND MPE_H "${PROJECT_SOURCE_DIR}/Platform/macOS/App/macOSContext.h")
endif()

# set_source_files_properties(${MPE_OSX_CPP} PROPERTIES COMPILE_FLAGS "-include MPE/MPEPCH.h")

# PRINT MPE macOS SOURCE FILES
if(${VERBOSE})
  message("
MPE macOS SOURCE AND HEADER FILES

macOS SOURCE FILES:\n")

  foreach(MPE_macOS_CPP_FILE ${MPE_macOS_CPP})
    message("${MPE_macOS_CPP_FILE}")
  endforeach()

  message("
macOS HEADER FILES:\n")

  foreach(MPE_macOS_H_FILE ${MPE_macOS_H})
    message("${MPE_macOS_H_FILE}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()