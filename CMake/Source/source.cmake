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
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/ShaderUtils.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Text/TextRenderer.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture2D.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/TextTexture.cpp"

    # /Editor
    "${PROJECT_SOURCE_DIR}/MPE/Editor/Grid/Grid.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Editor/Dialog/SimpleDialog.cpp"

    # /Sound
    "${PROJECT_SOURCE_DIR}/MPE/Sound/OpenALContext.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Sound/SoundPlayer.cpp"

    "${PROJECT_SOURCE_DIR}/MPE/Sound/Players/WavSoundPlayer.cpp"
    "${PROJECT_SOURCE_DIR}/MPE/Sound/Players/OggSoundPlayer.cpp"

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

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/Shader.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/ShaderLibrary.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/ShaderUtils.h"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Text/Character.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Text/TextRenderer.h"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture2D.h"
    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/TextTexture.h"

    "${PROJECT_SOURCE_DIR}/MPE/Renderer/Utilties/RenderInfo.h"

    # /Editor
    "${PROJECT_SOURCE_DIR}/MPE/Editor/Grid/Grid.h"

    "${PROJECT_SOURCE_DIR}/MPE/Editor/Dialog/SimpleDialog.h"

    # /Sound
    "${PROJECT_SOURCE_DIR}/MPE/Sound/OpenALContext.h"
    "${PROJECT_SOURCE_DIR}/MPE/Sound/SoundPlayer.h"

    "${PROJECT_SOURCE_DIR}/MPE/Sound/Players/WavSoundPlayer.h"
    "${PROJECT_SOURCE_DIR}/MPE/Sound/Players/OggSoundPlayer.h"

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