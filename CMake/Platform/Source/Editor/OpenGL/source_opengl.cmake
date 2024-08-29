file(
    GLOB_RECURSE
    MPE_EDITOR_OPENGL_CPP

    # /Editor/Platform/OpenGL/Editor
    "${PROJECT_SOURCE_DIR}/Editor/Platform/OpenGL/Editor/Grid/OpenGLGrid.cpp"
    "${PROJECT_SOURCE_DIR}/Editor/Platform/OpenGL/Editor/Utilities/OpenGLDebugGuiLayer.cpp"
)

file(
    GLOB_RECURSE
    MPE_EDITOR_OPENGL_H

    # /Editor/Platform/OpenGL/Editor
    "${PROJECT_SOURCE_DIR}/Editor/Platform/OpenGL/Editor/Grid/OpenGLGrid.h"
    "${PROJECT_SOURCE_DIR}/Editor/Platform/OpenGL/Editor/Utilities/OpenGLDebugGuiLayer.h"
)

# ADD MPE OPENGL SOURCE FILES
list(APPEND MPE_EDITOR_CPP ${MPE_EDITOR_OPENGL_CPP})

list(APPEND MPE_EDITOR_H ${MPE_EDITOR_OPENGL_H})

# PRINT MPE OPENGL SOURCE FILES
if(${VERBOSE})
    message("
MPE EDITOR OPENGL SOURCE AND HEADER FILES

OPENGL SOURCE FILES:\n")

    foreach(MPE_EDITOR_OPENGL_CPP_FILE ${MPE_EDITOR_OPENGL_CPP})
        message("${MPE_EDITOR_OPENGL_CPP_FILE}")
    endforeach()

    message("
OPENGL HEADER FILES:\n")

    foreach(MPE_EDITOR_OPENGL_H_FILE ${MPE_EDITOR_OPENGL_H})
        message("${MPE_EDITOR_OPENGL_H_FILE}")
    endforeach()

    message("
-----------------------------------------------------------")
endif()