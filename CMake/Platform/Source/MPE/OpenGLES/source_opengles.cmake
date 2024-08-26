file(
    GLOB_RECURSE
    MPE_OPENGLES_CPP

    # /Platform/OpenGLES
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESContext.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESRendererAPI.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESSettings.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESIndexBuffer.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESVertexArray.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESVertexBuffer.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Shaders/OpenGLESShader.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Text/OpenGLESTextRenderer.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Textures/OpenGLESTexture.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Textures/OpenGLESTexture2D.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Textures/OpenGLESTextTexture.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Utilities/OpenGLESUtilities.cpp"
)

file(
    GLOB_RECURSE
    MPE_OPENGLES_H

    "${PROJECT_SOURCE_DIR}/MPE/MPEGFX_OPEN_GL_ES.h"

    # /Platform/OpenGLES
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESContext.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESRendererAPI.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/OpenGLESSettings.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESIndexBuffer.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESVertexArray.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Pipeline/OpenGLESVertexBuffer.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Shaders/OpenGLESShader.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Text/OpenGLESTextRenderer.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Textures/OpenGLESTexture.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Textures/OpenGLESTexture2D.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Textures/OpenGLESTextTexture.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGLES/Utilities/OpenGLESUtilities.h"
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