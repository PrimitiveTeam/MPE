file(
    GLOB_RECURSE
    MPE_EDITOR_RPI4_CPP
)

file(
    GLOB_RECURSE
    MPE_EDITOR_RPI4_H
)

# ADD MPE RPI SOURCE FILES
list(APPEND MPE_EDITOR_CPP ${MPE_EDITOR_RPI4_CPP})

list(APPEND MPE_EDITOR_H ${MPE_EDITOR_RPI4_H})

# PRINT MPE RPI SOURCE FILES
if(${VERBOSE})
    message("
MPE RPI4 SOURCE AND HEADER FILES

RPI4 SOURCE FILES:\n")

    foreach(MPE_EDITOR_RPI4_CPP_FILE ${MPE_EDITOR_RPI4_CPP})
        message("${MPE_EDITOR_RPI4_CPP_FILE}")
    endforeach()

    message("   
RPI4 HEADER FILES:\n")

    foreach(MPE_EDITOR_RPI4_H_FILE ${MPE_EDITOR_RPI4_H})
        message("${MPE_EDITOR_RPI4_H_FILE}")
    endforeach()

    message("
-----------------------------------------------------------")
endif()