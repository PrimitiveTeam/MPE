#include "source/Pong.h"
#include "MPE/EntryPoint.h"

// TODO: CREATE LAMBDA LIKE PROJECT / TEST SELECTOR

class ProjectSelector : public MPE::App
{
  public:
    ProjectSelector()
    {
#ifdef MPE_DYNAMIC_LIBRARY
        ImGui::SetCurrentContext(this->GetImGuiContext());
#endif
        PushLayer(MPE::NEWREF<PONG::Pong>());
    }

    ~ProjectSelector() {}
};

MPE::App *MPE::CreateApp()
{
    return new ProjectSelector();
}