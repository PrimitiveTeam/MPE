file(
  GLOB_RECURSE
  MPE_EDITOR_Linux_CPP
)

file(
  GLOB_RECURSE
  MPE_EDITOR_Linux_H
)

# ADD MPE Linux SOURCE FILES
list(APPEND MPE_CPP ${MPE_EDITOR_Linux_CPP})

list(APPEND MPE_H ${MPE_EDITOR_Linux_H})

# PRINT MPE Linux SOURCE FILES
if(${VERBOSE})
  message("
MPE LINUX SOURCE AND HEADER FILES

LINUX SOURCE FILES:\n")

  foreach(MPE_EDITOR_LINUX_CPP_FILE ${MPE_EDITOR_LINUX_CPP})
    message("${MPE_EDITOR_LINUX_CPP_FILE}")
  endforeach()

  message("
LINUX HEADER FILES:\n")

  foreach(MPE_EDITOR_LINUX_H_FILE ${MPE_EDITOR_LINUX_H})
    message("${MPE_EDITOR_LINUX_H_FILE}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()