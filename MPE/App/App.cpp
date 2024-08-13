#include "App.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_CORE.h"
#include "MPE/App/Layers/LayerStack.h"
#include "MPE/Input/Input.h"
// #include "MPE/Platform/Windows/Input/WindowsInput.h"

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

// TODO: Add a dialog to select the graphics API
// Set RenderAPI before creating window
// Renderer::SetGraphicsAPI(RendererAPI::API::OpenGLES);
#ifdef MPE_PLATFORM_RPI4
    Renderer::SetGraphicsAPI(RendererAPI::API::OpenGLES);
#else
#    if MPE_OPENGL
    Renderer::SetGraphicsAPI(RendererAPI::API::OpenGL);
#    elif MPE_OPENGLES
    Renderer::SetGraphicsAPI(RendererAPI::API::OpenGLES);
#    else
    MPE_ASSERT(false, "NO GRAPHICS API SELECTED.");
#    endif
#endif

    // Critical log to show which API we are using
    MPE_WARN("Using {0} API", RendererAPI::APIToString(RendererAPI::GetGraphicsAPI()));

    auto mpeVersion = "MPE v" + std::string(MPE_FULL_VERSION);

    SYS_APP_Window = Window::CreateNativeWindow(WindowProps(mpeVersion, 1280, 720));
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
        if (SYS_AppPaused) continue;

        auto frameStart = std::chrono::high_resolution_clock::now();

        // TODO: Platform::GetTime();
        float time = (float) glfwGetTime();
        Time deltaTime = time - SYS_LAST_FRAME_TIME;
        SYS_LAST_FRAME_TIME = time;

        Renderer::UpdateFPS_MS(deltaTime);

        if (IsDeltaTimePaused)
        {
            deltaTime = 0.0f;
        }

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

        if (Input::IsKeyJustPressed(MPE_KEY_SPACE)) ToggleDeltaTime();

        // Calculate frame time
        auto frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> frameDuration = frameEnd - frameStart;

        // If frame completed too fast, delay to maintain target frame time
        if (SYS_TargetFPS != -1 && (frameDuration.count() < SYS_Frame_Time_MS))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(SYS_Frame_Time_MS) - frameDuration);
        }
    }
}

void App::OnEvent(Event &SYS_Event)
{
    EventDispatcher dispatcher(SYS_Event);
    dispatcher.Dispatch<WindowCloseEvent>(MPE_BIND_EVENT_FUNCTION(App::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(App::OnWindowResize));
    dispatcher.Dispatch<WindowMovedEvent>(MPE_BIND_EVENT_FUNCTION(App::OnWindowMoved));
    dispatcher.Dispatch<GraphicsSettingsChangedEvent>(MPE_BIND_EVENT_FUNCTION(App::OnGraphicsSettingsUpdate));

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

    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
    SYS_APP_Window->SetLastWindowSize(e.GetWidth(), e.GetHeight());

    return false;
}

bool App::OnWindowMoved(WindowMovedEvent &e)
{
    // While window is moved SYS_AppPaused = true;

    if (e.GetX() == SYS_APP_Window->GetWindowPositionX() && e.GetY() == SYS_APP_Window->GetWindowPositionY())
    {
        SYS_AppPaused = false;
    }
    else
    {
        SYS_AppPaused = true;
    }
    SYS_APP_Window->SetLastWindowPosition(e.GetX(), e.GetY());

    return false;
}

void App::ToggleFullscreen()
{
    if (SYS_APP_Window != nullptr)
    {
        SYS_APP_Window->ToggleFullScreen();
    }
}

void App::ToggleDeltaTime()
{
    IsDeltaTimePaused = !IsDeltaTimePaused;
}

bool App::OnGraphicsSettingsUpdate(GraphicsSettingsChangedEvent &e)
{
    // Get settings from renderer then update appropriate settings like frame lock

    auto rendererSettings = RenderPrimitive::GetSettings();

    if (e.GetSettingName() == "LIMIT_FPS" || e.GetSettingName() == "MAX_FPS")
    {
        if (rendererSettings->GetLimitFPS())
        {
            SYS_TargetFPS = rendererSettings->GetMaxFPS();
            SYS_Frame_Time_MS = 1000.0f / SYS_TargetFPS;
        }
        else
        {
            SYS_TargetFPS = -1;
        }
    }

    return false;
}
}