#pragma once

/**
 * @file MPE.h
 * @brief Precompiled header file for the MPE engine.
 * @details This file is used to include all the necessary headers for the MPE engine.
 * Use this file to include all the necessary headers for an external application.
 * @date 2024-05-05
 */

// ----- CORE INTERNAL -----
// #include "MPE/Core/App.h"
// #include "MPE/Core/Layers/Layer.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Core/_CWD.h"
// ----- CORE INTERNAL -----

// ----- LOG -----
#include "MPE/Log/GlobalLog.h"
#include "MPE/Log/Log.h"
// ----- LOG -----

// ----- APPLICATION -----
// #include "MPE/Core/App.h"
// #include "MPE/Core/Layers/Layer.h"
// ----- APPLICATION -----

// ----- PHYSICS -----
// #include "MPE/Core/_TIME.h"
// ----- PHYSICS -----

// ----- PROFILING -----
// ONLY FOR DEBUGGING!
#include "MPE/Profiling/_TIMER.h"
#include "MPE/Profiling/_PROFILING.h"
// ----- PROFILING -----

// ----- EVENTS -----
// #include "MPE/Core/Events/EventApp.h"
// #include "MPE/Core/Events/EventKey.h"
// #include "MPE/Core/Events/EventMouse.h"
// ----- EVENTS -----

// ----- INPUT -----
// #include "MPE/Core/Input/Input.h"
// #include "MPE/Core/Input/KeyCodes.h"
// #include "MPE/Core/Input/MouseButtonCodes.h"
// ----- INPUT -----

// ----- IMGUI -----
// #include "MPE/Vendor/ImGui/ImGuiLayer.h"
// ----- IMGUI -----

// ----- RENDERER -----
// #include "MPE/Renderer/Renderer.h"
// #include "MPE/Renderer/Renderer2D.h"
// #include "MPE/Renderer/RenderPrimitive.h"
// ----- RENDERER -----

// ----- GRAPHICS -----
// #include "MPE/Renderer/Pipeline/VertexBuffer.h"
// #include "MPE/Renderer/Pipeline/IndexBuffer.h"
// #include "MPE/Renderer/Pipeline/VertexArray.h"
// #include "MPE/Renderer/Shaders/Shader.h"
// #include "MPE/Renderer/Textures/Texture.h"
// #include "MPE/Renderer/Textures/Texture2D.h"
// ----- GRAPHICS -----

// ----- CAMERAS -----
// #include "MPE/Renderer/Cameras/OrthographicCamera.h"
// #include "MPE/Renderer/Cameras/OrthographicCameraController.h"
// #include "MPE/Renderer/Cameras/StaticOrthographicCamera.h"
// ----- CAMERAS -----

//-----Entry Point----
// #include "MPE/Core/EntryPoint.h"
//-----Entry Point----