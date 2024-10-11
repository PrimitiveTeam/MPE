#pragma once

#include "MPE.h"
#include "MPEECS.h"
#include "MPEEDITOR.h"

#include <imgui.h>
#include <string>
#include <vector>

class ObjectHierarchyTest : public MPE::Layer
{
  public:
    ObjectHierarchyTest();

    virtual ~ObjectHierarchyTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    void AddCubeObject();
    void AddSphereObject();
    void RemoveObject();

  private:
    MPE::SCOPE<std::string> m_layerName;

    // Scene
    MPE::SCOPE<MPE::SceneManager> m_sceneManager;
    MPE::REF<MPE::Scene> m_scene;
    MPE::REF<MPE::ObjectHierarchy> m_objectHierarchy;
};
