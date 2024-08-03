file(
  GLOB_RECURSE
  MPE_macOS_CPP

  # /Platform/macOS/Core
  "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Core/*.mm"

  # /Platform/macOS/App
  "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/App/*.cpp"

  # /Platform/macOS/Errors
  "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Errors/*.mm"

  # /Platform/macOS/Input
  "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Input/*.cpp"
)

file(
  GLOB_RECURSE
  MPE_macOS_H

  # /Platform/macOS/Core
  "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Core/*.h"

  # /Platform/macOS/App
  "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/App/*.h"

  # /Platform/macOS/Input
  "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Input/*.h"
)

# ADD MPE macOS SOURCE FILES
list(APPEND MPE_CPP ${MPE_macOS_CPP})

list(APPEND MPE_H ${MPE_macOS_H})

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