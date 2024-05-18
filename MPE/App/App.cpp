#include "App.h"
#include "MPE/MPEPCH.h"

#include "MPE/App/Layers/LayerStack.h"
#include "MPE/Core/_INIT.h"

namespace MPE
{
App::App()
{
    SYS_Log = MPE::Log::Create("App", MPE::Log::Option::CONSOLE);
    SYS_LayerStack = NEWREF<LayerStack>();
    
    SYS_Window = Window::CreateNativeWindow(WindowProps("MPE Engine", 1280, 720));
    SYS_Window->SetEventCallback(MPE_BIND_EVENT_FUNCTION(MPE::App::OnEvent));

    // Initialize Renderer
    // Initialize ImGuiLayer and push to overlay layer
}

App::~App() {}

void App::Initialize()
{
    MPE_CORE_ASSERT(!SYS_Instance, "APP ALREADY EXISTS.");
    SYS_Instance = shared_from_this();
}

REF<App> CreateApp()
{
    auto app = std::make_shared<App>();
    app->Initialize();
    return app;
    // return NEWREF<App>();
}

void App::Run()
{
    while (SYS_Running)
    {
        SYS_Log->info("Running...");

        // Platform::GetTime();
        // glfwGetTime() would be used here but for now we need a simple timer to keep track of the time passed since the last frame
        float time = 0.0f;
        Time deltaTime = time - 0.0f;

        if (!SYS_Minimized)
        {
            // Using the ref system to iterate through the layers
            // REF<MPE::LayerStack> SYS_LayerStack;
            for (REF<Layer> layer : *SYS_LayerStack)
            {
                layer->OnUpdate(deltaTime);
            }
        }

        // SYS_Window->OnUpdate();

        Shutdown();
    }
}

void App::OnEvent(Event &SYS_Event)
{
    EventDispatcher dispatcher(SYS_Event);

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
        // auto it = SYS_LayerStack->end();
        // it->get()->OnDetach();
        // SYS_LayerStack->PopLayer(*it);
        SYS_LayerStack->PopLayer();
    }
}

void App::PopAllLayers()
{
    while (!SYS_LayerStack->empty())
    {
        // auto it = SYS_LayerStack->end();
        // it->get()->OnDetach();
        // SYS_LayerStack->PopLayer(*it);
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
        // auto it = SYS_LayerStack->end();
        // it->get()->OnDetach();
        // SYS_LayerStack->PopOverlay(*it);
        SYS_LayerStack->PopOverlay();
    }
}

void App::PopAllOverlays()
{
    while (!SYS_LayerStack->empty())
    {
        // auto it = SYS_LayerStack->end();
        // it->get()->OnDetach();
        // SYS_LayerStack->PopOverlay(*it);
        SYS_LayerStack->PopOverlay();
    }
}
}