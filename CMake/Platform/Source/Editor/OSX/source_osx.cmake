file(
  GLOB_RECURSE
  MPE_EDITOR_macOS_CPP
)

file(
  GLOB_RECURSE
  MPE_EDITOR_macOS_H
)

# ADD MPE macOS SOURCE FILES
list(APPEND MPE_EDITOR_CPP ${MPE_EDITOR_macOS_CPP})

list(APPEND MPE_EDITOR_H ${MPE_EDITOR_macOS_H})

# set_source_files_properties(${MPE_OSX_CPP} PROPERTIES COMPILE_FLAGS "-include MPE/MPEPCH.h")

# PRINT MPE macOS SOURCE FILES
if(${VERBOSE})
  message("
MPE macOS SOURCE AND HEADER FILES

macOS SOURCE FILES:\n")

  foreach(MPE_EDITOR_macOS_CPP_FILE ${MPE_EDITOR_macOS_CPP})
    message("${MPE_EDITOR_macOS_CPP_FILE}")
  endforeach()

  message("
macOS HEADER FILES:\n")

  foreach(MPE_EDITOR_macOS_H_FILE ${MPE_EDITOR_macOS_H})
    message("${MPE_EDITOR_macOS_H_FILE}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()