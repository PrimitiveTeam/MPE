#include "MPE/EntryPoint.h"
#include "MPE/MPE.h"
#include "Editor/MPEECS.h"
#include "Editor/MPEEDITOR.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#    include "Platform/OpenGL/Editor/Utilities/OpenGLDebugGuiLayer.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#    include "Platform/OpenGLES/Editor/Utilities/OpenGLESDebugGuiLayer.h"
#endif

#include <imgui.h>
#include "MPE/Vendor/GLM/GLM.h"

class EditorCoreLayer : public MPE::Layer
{
  public:
    EditorCoreLayer() : Layer("EditorCoreLayer") {}

    void OnAttach() override {}

    void OnDetach() override {}

    void OnUpdate(MPE::Time deltaTime) override {}

    void OnImGuiRender() override
    {
        ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoSavedSettings);

        ImGui::End();
    }

    void OnEvent(MPE::Event& event) override {}

  private:
};

class Editor : public MPE::App
{
  public:
    Editor()
    {
#ifdef MPE_DYNAMIC_LIBRARY
        ImGui::SetCurrentContext(this->GetImGuiContext());
#endif
#ifdef MPE_OPENGL
        PushLayer(MPE::NEWREF<MPE::OpenGLDebugGuiLayer>());
#elif MPE_OPENGLES
        PushLayer(MPE::NEWREF<MPE::OpenGLESDebugGuiLayer>());
#endif
        PushOverlay(MPE::NEWREF<EditorCoreLayer>());
    }

    ~Editor() {}
};

MPE::App* MPE::CreateApp()
{
    return new Editor();
}