file(
    GLOB_RECURSE
    MPE_RPI4_CPP

    # /Platform/RPI/Core
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/Core/*.cpp"

    # /Platform/RPI/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/App/*.cpp"

    # /Platform/RPI/Errors
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/Errors/*.cpp"

    # /Platform/RPI/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/Input/*.cpp"
)

file(
    GLOB_RECURSE
    MPE_RPI4_H

    # /Platform/RPI/Core
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/Core/*.h"

    # /Platform/RPI/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/App/*.h"

    # /Platform/RPI/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/Input/*.h"
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