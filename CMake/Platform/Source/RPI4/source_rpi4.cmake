file(
    GLOB_RECURSE
    MPE_RPI4_CPP

    # /Platform/RPI/App
    "${PROJECT_SOURCE_DIR}/Platform/RPI/App/RPIWindow.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/RPI/App/WindowMonitors.cpp"

    # /Platform/RPI/Core
    "${PROJECT_SOURCE_DIR}/Platform/RPI/Core/_PTRS.cpp"

    # /Platform/RPI/Errors
    "${PROJECT_SOURCE_DIR}/Platform/RPI/Errors/Error.cpp"

    # /Platform/RPI/Input
    "${PROJECT_SOURCE_DIR}/Platform/RPI/Input/RPIInput.cpp"
)

file(
    GLOB_RECURSE
    MPE_RPI4_H

    # /Platform/RPI/App
    "${PROJECT_SOURCE_DIR}/Platform/RPI/App/RPIWindow.h"
    "${PROJECT_SOURCE_DIR}/Platform/RPI/App/WindowMonitors.h"

    # /Platform/RPI/Input
    "${PROJECT_SOURCE_DIR}/Platform/RPI/Input/RPIInput.h"
)

# ADD MPE RPI SOURCE FILES
list(APPEND MPE_CPP ${MPE_RPI4_CPP})

list(APPEND MPE_H ${MPE_RPI4_H})

# PRINT MPE RPI SOURCE FILES
if(${VERBOSE})
    message("
MPE RPI4 SOURCE AND HEADER FILES

RPI4 SOURCE FILES:\n")

    foreach(MPE_RPI4_CPP_FILE ${MPE_RPI4_CPP})
        message("${MPE_RPI4_CPP_FILE}")
    endforeach()

    message("   
RPI4 HEADER FILES:\n")

    foreach(MPE_RPI4_H_FILE ${MPE_RPI4_H})
        message("${MPE_RPI4_H_FILE}")
    endforeach()

    message("
-----------------------------------------------------------")
endif()