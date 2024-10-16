file(
    GLOB_RECURSE
    MPE_CPP

    # TEST
    "${PROJECT_SOURCE_DIR}/MPE/Test/Test.cpp"

    # /Core
    "${PROJECT_SOURCE_DIR}/MPE/Core/_PTRS.cpp"

    # /Log
    "${PROJECT_SOURCE_DIR}/MPE/Log/Log.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Log/GlobalLog.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Log/CustomSinks/MemorySink.cpp"

    # /Errors
    "${PROJECT_SOURCE_DIR}/MPE/Errors/Error.cpp"

    # /App
    "${PROJECT_SOURCE_DIR}/MPE/App/App.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/App/Window.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/App/WindowProps.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/App/Layers/Layer.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/App/Layers/LayerStack.cpp"

    # /Profiling
    "${PROJECT_SOURCE_DIR}/MPE/Profiling/_PROFILING.cpp"

    # /Physics
    "${PROJECT_SOURCE_DIR}/MPE/Time/Time.cpp"

    # /Input
    "${PROJECT_SOURCE_DIR}/MPE/Input/KeyState.cpp"

    # /Events
    "${PROJECT_SOURCE_DIR}/MPE/Events/EventApp.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Events/EventFunction.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Events/EventGraphics.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Events/EventKey.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Events/EventMouse.cpp"

    # /Renderer
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Renderer.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Renderer2D.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/RendererAPI.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/RendererUtilities.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderPrimitive.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderSettings.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/OrthographicCamera.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/OrthographicCameraController.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/StaticOrthographicCamera.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/BufferLayout.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/IndexBuffer.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/VertexArray.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/VertexBuffer.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderInformation/RenderInfo.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/Shader.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/ShaderLibrary.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture2D.cpp"

    # /Editor
    "${PROJECT_SOURCE_DIR}/MPE/Editor/Grid/Grid.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Editor/Dialog/SimpleDialog.cpp"

    # /Platform/OpenGL
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLContext.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLContextProps.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLRendererAPI.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLSettings.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Editor/Grid/OpenGLGrid.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLIndexBuffer.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLVertexArray.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLVertexBuffer.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Shaders/OpenGLShader.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Textures/OpenGLTexture.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Textures/OpenGLTexture2D.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Utilities/OpenGLUtilities.cpp"

    # /Platform/OpenGLES
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESContext.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESContextProps.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESRendererAPI.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESSettings.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Editor/Grid/OpenGLESGrid.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESIndexBuffer.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESVertexArray.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESVertexBuffer.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Shaders/OpenGLESShader.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Textures/OpenGLESTexture.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Textures/OpenGLESTexture2D.cpp"

    # /Vendor
    "${PROJECT_SOURCE_DIR}/MPE/Vendor/ImGui/ImGuiLayer.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Vendor/STB/stb_image_impl.cpp"
)

# MPE LIBRARY .H FILES
file(
    GLOB_RECURSE
    MPE_H

    # TEST
    "${PROJECT_SOURCE_DIR}/MPE/Test/Test.h"

    # /
    "${PROJECT_SOURCE_DIR}/MPE/EntryPoint.h"
    "${PROJECT_SOURCE_DIR}/MPE/MPE.h"
    "${PROJECT_SOURCE_DIR}/MPE/MPEPCH.h"
    "${PROJECT_SOURCE_DIR}/MPE/MPEPLAT.h"

    # /Core
    "${PROJECT_SOURCE_DIR}/MPE/Core/_VERSION.h"
    "${PROJECT_SOURCE_DIR}/MPE/Core/_ASSERTS.h"
    "${PROJECT_SOURCE_DIR}/MPE/Core/_CORE.h"
    "${PROJECT_SOURCE_DIR}/MPE/Core/_CWD.h"
    "${PROJECT_SOURCE_DIR}/MPE/Core/_INIT.h"
    "${PROJECT_SOURCE_DIR}/MPE/Core/_PTRS.h"

    # /Log
    "${PROJECT_SOURCE_DIR}/MPE/Log/Log.h"
    "${PROJECT_SOURCE_DIR}/MPE/Log/GlobalLog.h"
    "${PROJECT_SOURCE_DIR}/MPE/Log/CustomSinks/MemorySink.h"

    # /Errors
    "${PROJECT_SOURCE_DIR}/MPE/Errors/Error.h"
    "${PROJECT_SOURCE_DIR}/MPE/Errors/Errors.h"

    # /App
    "${PROJECT_SOURCE_DIR}/MPE/App/App.h"
    "${PROJECT_SOURCE_DIR}/MPE/App/Window.h"
    "${PROJECT_SOURCE_DIR}/MPE/App/WindowProps.h"
    "${PROJECT_SOURCE_DIR}/MPE/App/Layers/Layer.h"
    "${PROJECT_SOURCE_DIR}/MPE/App/Layers/LayerStack.h"

    # /Profiling
    "${PROJECT_SOURCE_DIR}/MPE/Profiling/_PROFILING.h"
    "${PROJECT_SOURCE_DIR}/MPE/Profiling/_TIMER.h"

    # /Physics
    "${PROJECT_SOURCE_DIR}/MPE/Time/Time.h"

    # /Input
    "${PROJECT_SOURCE_DIR}/MPE/Input/Input.h"
    "${PROJECT_SOURCE_DIR}/MPE/Input/KeyCodes.h"
    "${PROJECT_SOURCE_DIR}/MPE/Input/KeyState.h"
    "${PROJECT_SOURCE_DIR}/MPE/Input/MouseButtonCodes.h"

    # /Events
    "${PROJECT_SOURCE_DIR}/MPE/Events/Event.h"
    "${PROJECT_SOURCE_DIR}/MPE/Events/EventApp.h"
    "${PROJECT_SOURCE_DIR}/MPE/Events/EventFunction.h"
    "${PROJECT_SOURCE_DIR}/MPE/Events/EventGraphics.h"
    "${PROJECT_SOURCE_DIR}/MPE/Events/EventKey.h"
    "${PROJECT_SOURCE_DIR}/MPE/Events/EventMouse.h"

    # /Renderer
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/GraphicalContext.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/GraphicalContextProps.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Renderer.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Renderer2D.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/RendererAPI.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/RendererUtilities.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderPrimitive.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderSettings.h"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/OrthographicCamera.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/OrthographicCameraController.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/StaticOrthographicCamera.h"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/BufferLayout.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/IndexBuffer.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/VertexArray.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/VertexBuffer.h"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderInformation/RenderInfo.h"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/Shader.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/ShaderLibrary.h"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture2D.h"

    # /Editor
    "${PROJECT_SOURCE_DIR}/MPE/Editor/Grid/Grid.h"

    "${PROJECT_SOURCE_DIR}/MPE/Editor/Dialog/SimpleDialog.h"

    # /Platform/OpenGL
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLContext.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLContextProps.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLRendererAPI.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLSettings.h"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Editor/Grid/OpenGLGrid.h"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLIndexBuffer.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLVertexArray.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLVertexBuffer.h"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Shaders/OpenGLShader.h"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Textures/OpenGLTexture.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Textures/OpenGLTexture2D.h"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Utilities/OpenGLUtilities.h"

    # /Platform/OpenGLES
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESContext.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESContextProps.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESRendererAPI.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESSettings.h"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Editor/Grid/OpenGLESGrid.h"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESIndexBuffer.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESVertexArray.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESVertexBuffer.h"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Shaders/OpenGLESShader.h"

    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Textures/OpenGLESTexture.h"
    "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Textures/OpenGLESTexture2D.h"

    # /Vendor
    "${PROJECT_SOURCE_DIR}/MPE/Vendor/ImGui/ImGuiLayer.h"
    "${PROJECT_SOURCE_DIR}/MPE/Vendor/STB/stb_image.h"
)

# PRINT MPE SOURCE FILES
if(${VERBOSE})
    # message("
    # -----------------------------------------------------------
    # MPE HEADERS AND SOURCE FILES
    # -----------------------------------------------------------")
    message("
-----------------------------------------------------------
MPE HEADERS AND SOURCE FILES")

    message("
***********************************************************

CORE SOURCE FILES:\n")

    foreach(MPE_CPP_FILE ${MPE_CPP})
        message("${MPE_CPP_FILE}")
    endforeach()

    message("
CORE HEADER FILES:\n")

    foreach(MPE_H_FILE ${MPE_H})
        message("${MPE_H_FILE}")
    endforeach()

    message("
***********************************************************")
endif()