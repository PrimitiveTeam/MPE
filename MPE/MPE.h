#pragma once

/**
 * @file MPE.h
 * @brief Precompiled header file for the MPE engine.
 * @details This file is used to include all the necessary headers for the MPE
 * engine. Use this file to include all the necessary headers for an external
 * application.
 * @date 2024-05-05
 */

// ----- CORE INTERNAL -----
// #include "MPE/Core/App.h"
// #include "MPE/Core/Layers/Layer.h"
#include "MPE/Core/_ASSERTS.h"
#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CWD.h"
#include "MPE/Core/_CORE.h"
// ----- CORE INTERNAL -----

// ----- LOG -----
#include "MPE/Log/GlobalLog.h"
#include "MPE/Log/Log.h"
// ----- LOG -----

// ----- ERRORS -----
#include "MPE/Errors/Error.h"
#include "MPE/Errors/Errors.h"
// ----- ERRORS -----

// ----- APPLICATION -----
#include "MPE/App/App.h"
#include "MPE/App/Layers/Layer.h"
#include "MPE/App/Layers/LayerStack.h"
#include "MPE/App/WindowProps.h"
#include "MPE/App/Window.h"
// ----- APPLICATION -----

// ----- PROFILING -----
// ONLY FOR DEBUGGING!
#include "MPE/Profiling/_PROFILING.h"
#include "MPE/Profiling/_TIMER.h"
// ----- PROFILING -----

// ----- PHYSICS -----
#include "MPE/Time/Time.h"
// ----- PHYSICS -----

// ----- EVENTS -----
#include "MPE/Events/EventApp.h"
#include "MPE/Events/EventGraphics.h"
#include "MPE/Events/EventFunction.h"
#include "MPE/Events/EventKey.h"
#include "MPE/Events/EventMouse.h"
// ----- EVENTS -----

// ----- INPUT -----
#include "MPE/Input/Input.h"
#include "MPE/Input/KeyCodes.h"
#include "MPE/Input/MouseButtonCodes.h"
// ----- INPUT -----

// ----- IMGUI -----
#include "MPE/Vendor/ImGui/ImGuiLayer.h"
// ----- IMGUI -----

// ----- RENDERER -----
#include "MPE/Renderer/Renderer.h"
#include "MPE/Renderer/Renderer2D.h"
#include "MPE/Renderer/RenderPrimitive.h"
#include "MPE/Renderer/RendererUtilities.h"
// ----- RENDERER -----

// ----- GRAPHICS -----
#include "MPE/Renderer/Pipeline/VertexBuffer.h"
#include "MPE/Renderer/Pipeline/IndexBuffer.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Shaders/Shader.h"
#include "MPE/Renderer/Textures/Texture.h"
#include "MPE/Renderer/Textures/Texture2D.h"
// ----- GRAPHICS -----

// ----- CAMERAS -----
#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Renderer/Cameras/OrthographicCameraController.h"
#include "MPE/Renderer/Cameras/StaticOrthographicCamera.h"
// ----- CAMERAS -----

// ----- EDITOR -----
#include "MPE/Editor/Grid/Grid.h"
// ----- EDITOR -----
