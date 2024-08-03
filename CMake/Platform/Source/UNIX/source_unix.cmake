file(
  GLOB_RECURSE
  MPE_Linux_CPP

  # /Platform/Linux/Core
  "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Core/*.cpp"

  # /Platform/Linux/App
  "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/App/*.cpp"

  # /Platform/Linux/Errors
  "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Errors/*.cpp"

  # /Platform/Linux/Input
  "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Input/*.cpp"
)

file(
  GLOB_RECURSE
  MPE_Linux_H

  # /Platform/Linux/Core
  "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Core/*.h"

  # /Platform/Linux/App
  "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/App/*.h"

  # /Platform/Linux/Input
  "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Input/*.h"
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