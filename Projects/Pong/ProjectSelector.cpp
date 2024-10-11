#include "source/Pong.h"
#include "MPE/EntryPoint.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#    include "EDITOR/Platform/OpenGL/Editor/Utilities/OpenGLDebugGuiLayer.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#    include "EDITOR/Platform/OpenGLES/Editor/Utilities/OpenGLESDebugGuiLayer.h"
#endif

class ProjectSelector : public MPE::App
{
  public:
    ProjectSelector()
    {
#ifdef MPE_DYNAMIC_LIBRARY
        ImGui::SetCurrentContext(this->GetImGuiContext());
#endif
#ifdef MPE_OPENGL
        PushLayer(MPE::NEWREF<MPE::OpenGLDebugGuiLayer>());
#elif MPE_OPENGLES
        PushLayer(MPE::NEWREF<MPE::OpenGLESDebugGuiLayer>());
#endif
        PushLayer(MPE::NEWREF<PONG::Pong>());
    }

    ~ProjectSelector() {}
};

MPE::App* MPE::CreateApp()
{
    return new ProjectSelector();
}