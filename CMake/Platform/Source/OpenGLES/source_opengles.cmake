file(
    GLOB_RECURSE
    MPE_OPENGLES_CPP

    # /Platform/OpenGLES
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESContext.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESContextProps.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESRendererAPI.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESSettings.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Editor/Grid/OpenGLESGrid.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Editor/Utilities/OpenGLESDebugGuiLayer.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESIndexBuffer.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESVertexArray.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESVertexBuffer.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Shaders/OpenGLESShader.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Textures/OpenGLESTexture.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Textures/OpenGLESTexture2D.cpp"
)

file(
    GLOB_RECURSE
    MPE_OPENGLES_H

    "${PROJECT_SOURCE_DIR}/MPE/MPEGFX_OPEN_GL_ES.h"

    # /Platform/OpenGLES
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESContext.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESContextProps.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESRendererAPI.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESSettings.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Editor/Grid/OpenGLESGrid.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Editor/Utilities/OpenGLESDebugGuiLayer.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESIndexBuffer.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESVertexArray.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESVertexBuffer.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Shaders/OpenGLESShader.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Textures/OpenGLESTexture.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Textures/OpenGLESTexture2D.h"
)

# ADD MPE OPENGLES SOURCE FILES
list(APPEND MPE_CPP ${MPE_OPENGLES_CPP})

list(APPEND MPE_H ${MPE_OPENGLES_H})

# PRINT MPE OPENGLES SOURCE FILES
if(${VERBOSE})
    message("
MPE OPENGLES SOURCE AND HEADER FILES

OPENGLES SOURCE FILES:\n")

    foreach(MPE_OPENGLES_CPP_FILE ${MPE_OPENGLES_CPP})
        message("${MPE_OPENGLES_CPP_FILE}")
    endforeach()

    message("
OPENGLES HEADER FILES:\n")

    foreach(MPE_OPENGLES_H_FILE ${MPE_OPENGLES_H})
        message("${MPE_OPENGLES_H_FILE}")
    endforeach()

    message("
-----------------------------------------------------------")
endif()