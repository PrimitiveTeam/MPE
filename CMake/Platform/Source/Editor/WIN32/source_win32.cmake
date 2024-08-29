file(
  GLOB_RECURSE
  MPE_EDITOR_WIN32_CPP

  # /Platform/Windows/Editor/Prompts
  "${PROJECT_SOURCE_DIR}/Editor/Platform/Windows/Editor/Prompts/WindowsSimpleDialog.cpp"
)

file(
  GLOB_RECURSE
  MPE_EDITOR_WIN32_H
)

# ADD MPE WIN32 SOURCE FILES
list(APPEND MPE_CPP ${MPE_EDITOR_WIN32_CPP})

list(APPEND MPE_H ${MPE_EDITOR_WIN32_H})

# PRINT MPE WIN32 SOURCE FILES
if(${VERBOSE})
  message("
MPE WIN32 SOURCE AND HEADER FILES

WIN32 SOURCE FILES:\n")

  foreach(MPE_EDITOR_WIN32_CPP_FILE ${MPE_EDITOR_WIN32_CPP})
    message("${MPE_EDITOR_WIN32_CPP_FILE}")
  endforeach()

  message("
WIN32 HEADER FILES:\n")

  foreach(MPE_EDITOR_WIN32_H_FILE ${MPE_EDITOR_WIN32_H})
    message("${MPE_EDITOR_WIN32_H_FILE}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()