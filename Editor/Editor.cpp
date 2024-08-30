#include "MPE/EntryPoint.h"
#include "EditorSource.h"

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