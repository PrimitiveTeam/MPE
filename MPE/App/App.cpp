#include "App.h"
#include "MPE/MPEPCH.h"

#include "MPE/App/Layers/LayerStack.h"
#include "MPE/Core/_INIT.h"
#include "MPE/Input/Input.h"
#include "MPE/Platform/Windows/Input/WindowsInput.h"
#include "MPE/Core/_CORE.h"

// TEMP
#include <GLFW/glfw3.h>

namespace MPE
{
MPE_API App *App::SYS_APP_Instance = nullptr;

App::App()
{
    SYS_Log = MPE::Log::Create("App", MPE::Log::Option::CONSOLE);
    SYS_LayerStack = NEWREF<LayerStack>();

    MPE_CORE_ASSERT(!SYS_APP_Instance, "APP ALREADY EXISTS.");
    SYS_APP_Instance = this;

    SYS_APP_Window = Window::CreateNativeWindow(WindowProps("MPE Engine", 1280, 720));
    SYS_APP_Window->SetEventCallback(MPE_BIND_EVENT_FUNCTION(MPE::App::OnEvent));

    MPE_CORE_ASSERT(SYS_APP_Window, "NATIVE WINDOW NOT CREATED.");

    // Initialize Renderer
    // Initialize ImGuiLayer and push to overlay layer

    MPE_CORE_INFO("App instance initialized.");

    // SYS_APP_Window = Window::CreateNativeWindow(WindowProps("MPE Engine", 1280, 720));
    // SYS_APP_Window->SetEventCallback(MPE_BIND_EVENT_FUNCTION(MPE::App::OnEvent));

    // MPE_CORE_ASSERT(SYS_APP_Window, "NATIVE WINDOW NOT CREATED.");

    // Initialize Renderer
    // Initialize ImGuiLayer and push to overlay layer
}

App::~App()
{
    SYS_APP_Instance = nullptr;
}

void App::Run()
{
    while (SYS_APP_Running)
    {
        SYS_Log->info("Running...");

        // TODO: Platform::GetTime();
        float time = (float) glfwGetTime();
        Time deltaTime = time - SYS_LAST_FRAME_TIME;
        SYS_LAST_FRAME_TIME = time;

        if (!SYS_Minimized)
        {
            // Using the ref system to iterate through the layers
            // REF<MPE::LayerStack> SYS_LayerStack;
            for (REF<Layer> layer : *SYS_LayerStack)
            {
                layer->OnUpdate(deltaTime);
            }
        }

        SYS_APP_Window->OnUpdate();

        if (Input::IsKeyPressed(MPE_KEY_ESCAPE))
        {
            Shutdown();
        }
    }
}

void App::OnEvent(Event &SYS_Event)
{
    EventDispatcher dispatcher(SYS_Event);
    dispatcher.Dispatch<WindowCloseEvent>(MPE_BIND_EVENT_FUNCTION(App::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(App::OnWindowResize));

    for (auto it = SYS_LayerStack->end(); it != SYS_LayerStack->begin();)
    {
        (*--it)->OnEvent(SYS_Event);
        if (SYS_Event.SYS_Handled)
        {
            break;
        }
    }
}

void App::PushLayer(const REF<Layer> &Layer)
{
    SYS_LayerStack->PushLayer(Layer);
    Layer->OnAttach();
}

void App::PopLayer()
{
    if (!SYS_LayerStack->empty())
    {
        SYS_LayerStack->PopLayer();
    }
}

void App::PopAllLayers()
{
    while (!SYS_LayerStack->empty())
    {
        SYS_LayerStack->PopLayer();
    }
}

void App::PushOverlay(const REF<Layer> &Overlay)
{
    SYS_LayerStack->PushOverlay(Overlay);
    Overlay->OnAttach();
}

void App::PopOverlay()
{
    if (!SYS_LayerStack->empty())
    {
        SYS_LayerStack->PopOverlay();
    }
}

void App::PopAllOverlays()
{
    while (!SYS_LayerStack->empty())
    {
        SYS_LayerStack->PopOverlay();
    }
}

bool App::OnWindowClose(WindowCloseEvent &e)
{
    Shutdown();
    return true;
}

bool App::OnWindowResize(WindowResizeEvent &e)
{
    if (e.GetWidth() == 0 || e.GetHeight() == 0)
    {
        SYS_Minimized = true;
        return false;
    }
    SYS_Minimized = false;

    // Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

    return false;
}
}