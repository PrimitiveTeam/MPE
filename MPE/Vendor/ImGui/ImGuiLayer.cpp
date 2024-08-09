#include "ImGuiLayer.h"
#include "MPE/MPEPCH.h"

#include "MPE/App/App.h"

// #include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
// #include <imgui_impl_glfw.h>
// #include <imgui_impl_opengl3.h>
// TEMP

#ifdef MPE_OPENGL
#    include <glad/glad.h>
#endif
#include "GLFW/glfw3.h"
#ifdef MPE_OPENGLES
#    include <GLES3/gl31.h>
#endif

namespace MPE
{
App *ImGuiLayer::SYS_App = nullptr;

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
{
    SYS_App = &App::GetApp();
}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    // https://github.com/ocornut/imgui/issues/3169
    // "Globals are not shared accross DLL borders so you need to call ImGui::SetCurrentContext() on every side of the fence."

#ifdef MPE_DYNAMIC_LIBRARY
    SYS_ImGuiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(SYS_ImGuiContext);
#else
    ImGui::CreateContext();
#endif

    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
#ifdef MPE_OPENGL
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport / Platform Windows
#endif
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();
    //  When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // App &app = App::GetApp();
    GLFWwindow *window = static_cast<GLFWwindow *>(SYS_App->GetWindow()->GetNativeWindow());

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);

#ifdef MPE_OPENGL
#    ifdef MPE_PLATFORM_WINDOWS
    ImGui_ImplOpenGL3_Init("#version 410");
#    elif MPE_PLATFORM_OSX
    ImGui_ImplOpenGL3_Init("#version 150");
#    else
    ImGui_ImplOpenGL3_Init("#version 410");
#    endif
#elif MPE_OPENGLES
#    ifdef MPE_PLATFORM_OSX
    // Fallback to older implementation
    ImGui_ImplOpenGL3_Init("#version 140");
#    else
    ImGui_ImplOpenGL3_Init("#version 300 es");
#    endif
#endif
}

void ImGuiLayer::OnDetach()
{
#ifdef MPE_DYNAMIC_LIBRARY
    ImGui::SetCurrentContext(SYS_ImGuiContext);
#endif
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Begin()
{
#ifdef MPE_DYNAMIC_LIBRARY
    ImGui::SetCurrentContext(SYS_ImGuiContext);
#endif
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
#ifdef MPE_DYNAMIC_LIBRARY
    ImGui::SetCurrentContext(SYS_ImGuiContext);
#endif
    ImGuiIO &io = ImGui::GetIO();
    // App &app = App::GetApp();
    io.DisplaySize = ImVec2((float) SYS_App->GetWindow()->GetWidth(), (float) SYS_App->GetWindow()->GetHeight());

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void ImGuiLayer::OnImGuiRender()
{
#ifdef MPE_DYNAMIC_LIBRARY
    ImGui::SetCurrentContext(SYS_ImGuiContext);
#endif
    static bool show = false;
    if (show)
    {
        ImGui::ShowDemoWindow(&show);
    }
}
}