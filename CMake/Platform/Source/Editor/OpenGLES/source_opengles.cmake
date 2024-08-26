file(
    GLOB_RECURSE
    MPE_EDITOR_OPENGLES_CPP

    # /Editor/Platform/OpenGL/Editor
    "${PROJECT_SOURCE_DIR}/Editor/Platform/OpenGLES/Editor/Grid/OpenGLESGrid.cpp"
    "${PROJECT_SOURCE_DIR}/Editor/Platform/OpenGLES/Editor/Utilities/OpenGLESDebugGuiLayer.cpp"
)

file(
    GLOB_RECURSE
    MPE_EDITOR_OPENGLES_H

    # /Editor/Platform/OpenGL/Editor
    "${PROJECT_SOURCE_DIR}/Editor/Platform/OpenGLES/Editor/Grid/OpenGLESGrid.h"
    "${PROJECT_SOURCE_DIR}/Editor/Platform/OpenGLES/Editor/Utilities/OpenGLESDebugGuiLayer.h"
)

# ADD MPE OPENGLES SOURCE FILES
list(APPEND MPE_EDITOR_CPP ${MPE_EDITOR_OPENGLES_CPP})

list(APPEND MPE_EDITOR_H ${MPE_EDITOR_OPENGLES_H})

# PRINT MPE OPENGLES SOURCE FILES
if(${VERBOSE})
    message("
MPE OPENGLES SOURCE AND HEADER FILES

OPENGLES SOURCE FILES:\n")

    foreach(MPE_EDITOR_OPENGLES_CPP_FILE ${MPE_EDITOR_OPENGLES_CPP})
        message("${MPE_EDITOR_OPENGLES_CPP_FILE}")
    endforeach()

    message("
OPENGLES HEADER FILES:\n")

    foreach(MPE_EDITOR_OPENGLES_H_FILE ${MPE_EDITOR_OPENGLES_H})
        message("${MPE_EDITOR_OPENGLES_H_FILE}")
    endforeach()

    message("
-----------------------------------------------------------")
endif()