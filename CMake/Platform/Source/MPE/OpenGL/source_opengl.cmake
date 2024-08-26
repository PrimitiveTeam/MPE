file(
    GLOB_RECURSE
    MPE_OPENGL_CPP

    # /Platform/OpenGL
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/OpenGLContext.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/OpenGLRendererAPI.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/OpenGLSettings.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Pipeline/OpenGLIndexBuffer.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Pipeline/OpenGLVertexArray.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Pipeline/OpenGLVertexBuffer.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Shaders/OpenGLShader.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Text/OpenGLTextRenderer.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Textures/OpenGLTexture.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Textures/OpenGLTexture2D.cpp"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Textures/OpenGLTextTexture.cpp"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Utilities/OpenGLUtilities.cpp"
)

file(
    GLOB_RECURSE
    MPE_OPENGL_H

    "${PROJECT_SOURCE_DIR}/MPE/MPEGFX_OPEN_GL.h"

    # /Platform/OpenGL
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/OpenGLContext.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/OpenGLRendererAPI.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/OpenGLSettings.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Pipeline/OpenGLIndexBuffer.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Pipeline/OpenGLVertexArray.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Pipeline/OpenGLVertexBuffer.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Shaders/OpenGLShader.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Text/OpenGLTextRenderer.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Textures/OpenGLTexture.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Textures/OpenGLTexture2D.h"
    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Textures/OpenGLTextTexture.h"

    "${PROJECT_SOURCE_DIR}/Platform/OpenGL/Utilities/OpenGLUtilities.h"
)

# ADD MPE OPENGL SOURCE FILES
list(APPEND MPE_CPP ${MPE_OPENGL_CPP})

list(APPEND MPE_H ${MPE_OPENGL_H})

# PRINT MPE OPENGL SOURCE FILES
if(${VERBOSE})
    message("
MPE OPENGL SOURCE AND HEADER FILES

OPENGL SOURCE FILES:\n")

    foreach(MPE_OPENGL_CPP_FILE ${MPE_OPENGL_CPP})
        message("${MPE_OPENGL_CPP_FILE}")
    endforeach()

    message("
OPENGL HEADER FILES:\n")

    foreach(MPE_OPENGL_H_FILE ${MPE_OPENGL_H})
        message("${MPE_OPENGL_H_FILE}")
    endforeach()

    message("
-----------------------------------------------------------")
endif()