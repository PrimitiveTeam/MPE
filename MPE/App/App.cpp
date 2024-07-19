#include "App.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_CORE.h"
#include "MPE/App/Layers/LayerStack.h"
#include "MPE/Input/Input.h"
#include "MPE/Platform/Windows/Input/WindowsInput.h"

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

    Renderer::Init();

    SYS_ImGuiLayer = NEWREF<ImGuiLayer>();
    PushOverlay(SYS_ImGuiLayer);

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
        // TODO: Platform::GetTime();
        float time = (float) glfwGetTime();
        Time deltaTime = time - SYS_LAST_FRAME_TIME;
        SYS_LAST_FRAME_TIME = time;

        Renderer::UpdateFPS_MS(deltaTime);

        Input::Update();

        if (!SYS_Minimized)
        {
            // Using the ref system to iterate through the layers
            // REF<MPE::LayerStack> SYS_LayerStack;
            for (REF<Layer> layer : *SYS_LayerStack)
            {
                layer->OnUpdate(deltaTime);
            }
        }

        // TODO: If ImGui window is outside of the main window bounds it will be rendered but not interactable. Fix this.
        if (SYS_GUI)
        {
            SYS_ImGuiLayer->Begin();
            for (size_t i = 0; i < SYS_LayerStack->size(); ++i)
            {
                REF<Layer> layer = SYS_LayerStack->GetLayers()[i];

                if (layer) layer->OnImGuiRender();

                // Recalculate the index bounds in case the stack has been modified
                if (i >= SYS_LayerStack->GetLayers().size()) break;
            }
            SYS_ImGuiLayer->End();
        }

        // EVENT POLLING
        // auto[x, y] = Input::GetMousePosition();
        // MPE_CORE_ERROR("{0}, {1}", x, y);

        SYS_APP_Window->OnUpdate();

        if (Input::IsKeyJustPressed(MPE_KEY_ESCAPE)) Shutdown();

        if (Input::IsKeyJustPressed(MPE_KEY_F11)) ToggleGUI();

        if (Input::IsKeyJustPressed(MPE_KEY_F)) ToggleFullscreen();
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

void App::PopLayer(const REF<Layer> &Layer)
{
    if (!SYS_LayerStack->empty())
    {
        SYS_LayerStack->PopLayer(Layer);
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

void App::PopOverlay(const REF<Layer> &Overlay)
{
    if (!SYS_LayerStack->empty())
    {
        SYS_LayerStack->PopOverlay(Overlay);
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
    // SYS_APP_Window->SetLastWindowSize(e.GetWidth(), e.GetHeight());

    return false;
}

void App::ToggleFullscreen()
{
    if (SYS_APP_Window != nullptr)
    {
        SYS_APP_Window->ToggleFullScreen();
    }
}
}