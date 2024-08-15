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
MPE_API App *App::m_appInstance = nullptr;

App::App() : m_openalContext(OpenALContext::GetInstance())
{
    m_log = MPE::Log::Create("App", MPE::Log::Option::CONSOLE);
    m_layerStack = NEWREF<LayerStack>();

    MPE_CORE_ASSERT(!m_appInstance, "APP ALREADY EXISTS.");
    m_appInstance = this;

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

    m_appWindow = Window::CreateNativeWindow(WindowProps(mpeVersion, 1280, 720));
    m_appWindow->SetEventCallback(MPE_BIND_EVENT_FUNCTION(MPE::App::OnEvent));

    MPE_CORE_ASSERT(m_appWindow, "NATIVE WINDOW NOT CREATED.");

    Renderer::Init();

    m_imguiLayer = NEWREF<ImGuiLayer>();
    PushOverlay(m_imguiLayer);

    MPE_CORE_INFO("App instance initialized.");

    // m_appWindow = Window::CreateNativeWindow(WindowProps("MPE Engine", 1280, 720));
    // m_appWindow->SetEventCallback(MPE_BIND_EVENT_FUNCTION(MPE::App::OnEvent));

    // MPE_CORE_ASSERT(m_appWindow, "NATIVE WINDOW NOT CREATED.");

    // Initialize Renderer
    // Initialize ImGuiLayer and push to overlay layer
}

App::~App()
{
    if (m_isGuiOn)
    {
        for (size_t i = 0; i < m_layerStack->size(); ++i)
        {
            REF<Layer> layer = m_layerStack->GetLayers()[i];

            if (layer) layer->~Layer();

            // Recalculate the index bounds in case the stack has been modified
            if (i >= m_layerStack->GetLayers().size()) break;
        }
        m_imguiLayer->~ImGuiLayer();
    }

    // Explicitly destroy the OpenAL context before the window
    m_openalContext.~OpenALContext();

    m_appInstance = nullptr;
    MPE_CORE_INFO("App instance destroyed.");
}

void App::Run()
{
    while (m_isAppRunning)
    {
        if (m_isAppPaused) continue;

        auto frameStart = std::chrono::high_resolution_clock::now();

        // TODO: Platform::GetTime();
        float time = (float) glfwGetTime();
        Time deltaTime = time - m_lastFrameTime;
        m_lastFrameTime = time;

        Renderer::UpdateFpsMs(deltaTime);

        if (m_isDeltaTimePaused)
        {
            deltaTime = 0.0f;
        }

        Input::Update();

        if (!m_isAppMinimized)
        {
            // Using the ref system to iterate through the layers
            // REF<MPE::LayerStack> m_layerStack;
            for (REF<Layer> layer : *m_layerStack)
            {
                layer->OnUpdate(deltaTime);
            }
        }

        // TODO: If ImGui window is outside of the main window bounds it will be rendered but not interactable. Fix this.
        if (m_isGuiOn)
        {
            m_imguiLayer->Begin();
            for (size_t i = 0; i < m_layerStack->size(); ++i)
            {
                REF<Layer> layer = m_layerStack->GetLayers()[i];

                if (layer) layer->OnImGuiRender();

                // Recalculate the index bounds in case the stack has been modified
                if (i >= m_layerStack->GetLayers().size()) break;
            }
            m_imguiLayer->End();
        }

        // EVENT POLLING
        // auto[x, y] = Input::GetMousePosition();
        // MPE_CORE_ERROR("{0}, {1}", x, y);

        m_appWindow->OnUpdate();

        if (Input::IsKeyJustPressed(MPE_KEY_ESCAPE)) Shutdown();

        if (Input::IsKeyJustPressed(MPE_KEY_F11)) ToggleGUI();

        if (Input::IsKeyJustPressed(MPE_KEY_F)) ToggleFullscreen();

        if (Input::IsKeyJustPressed(MPE_KEY_SPACE)) ToggleDeltaTime();

        // Calculate frame time
        auto frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> frameDuration = frameEnd - frameStart;

        // If frame completed too fast, delay to maintain target frame time
        if (m_targetFPS != -1 && (frameDuration.count() < m_frameTimeMs))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(m_frameTimeMs) - frameDuration);
        }
    }
}

void App::OnEvent(Event &event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(MPE_BIND_EVENT_FUNCTION(App::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(App::OnWindowResize));
    dispatcher.Dispatch<WindowMovedEvent>(MPE_BIND_EVENT_FUNCTION(App::OnWindowMoved));
    dispatcher.Dispatch<GraphicsSettingsChangedEvent>(MPE_BIND_EVENT_FUNCTION(App::OnGraphicsSettingsUpdate));

    for (auto it = m_layerStack->end(); it != m_layerStack->begin();)
    {
        (*--it)->OnEvent(event);
        if (event.SYS_Handled)
        {
            break;
        }
    }
}

void App::PushLayer(const REF<Layer> &layer)
{
    m_layerStack->PushLayer(layer);
    layer->OnAttach();
}

void App::PopLayer()
{
    if (!m_layerStack->empty())
    {
        m_layerStack->PopLayer();
    }
}

void App::PopLayer(const REF<Layer> &layer)
{
    if (!m_layerStack->empty())
    {
        m_layerStack->PopLayer(layer);
    }
}

void App::PopAllLayers()
{
    while (!m_layerStack->empty())
    {
        m_layerStack->PopLayer();
    }
}

void App::PushOverlay(const REF<Layer> &overlay)
{
    m_layerStack->PushOverlay(overlay);
    overlay->OnAttach();
}

void App::PopOverlay()
{
    if (!m_layerStack->empty())
    {
        m_layerStack->PopOverlay();
    }
}

void App::PopOverlay(const REF<Layer> &overlay)
{
    if (!m_layerStack->empty())
    {
        m_layerStack->PopOverlay(overlay);
    }
}

void App::PopAllOverlays()
{
    while (!m_layerStack->empty())
    {
        m_layerStack->PopOverlay();
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
        m_isAppMinimized = true;
        return false;
    }
    m_isAppMinimized = false;

    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
    m_appWindow->SetLastWindowSize(e.GetWidth(), e.GetHeight());

    return false;
}

bool App::OnWindowMoved(WindowMovedEvent &e)
{
    // While window is moved m_isAppPaused = true;

    if (e.GetX() == m_appWindow->GetWindowPositionX() && e.GetY() == m_appWindow->GetWindowPositionY())
    {
        m_isAppPaused = false;
    }
    else
    {
        m_isAppPaused = true;
    }
    m_appWindow->SetLastWindowPosition(e.GetX(), e.GetY());

    return false;
}

void App::ToggleFullscreen()
{
    if (m_appWindow != nullptr)
    {
        m_appWindow->ToggleFullScreen();
    }
}

void App::ToggleDeltaTime()
{
    m_isDeltaTimePaused = !m_isDeltaTimePaused;
}

bool App::OnGraphicsSettingsUpdate(GraphicsSettingsChangedEvent &e)
{
    // Get settings from renderer then update appropriate settings like frame lock

    auto rendererSettings = RenderPrimitive::GetSettings();

    if (e.GetSettingName() == "LIMIT_FPS" || e.GetSettingName() == "MAX_FPS")
    {
        if (rendererSettings->GetLimitFPS())
        {
            m_targetFPS = rendererSettings->GetMaxFPS();
            m_frameTimeMs = 1000.0f / m_targetFPS;
        }
        else
        {
            m_targetFPS = -1;
        }
    }

    return false;
}
}