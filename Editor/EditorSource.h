#pragma once

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
    EditorCoreLayer();

    virtual void OnAttach() override;

    virtual void OnDetach() override;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event& event) override;

  private:
    MPE::SCOPE<MPE::SceneManager> m_sceneManager;
    MPE::REF<MPE::Scene> m_scene;
};