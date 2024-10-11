#pragma once

#include "MPE.h"
#include "MPEECS.h"
#include "MPEEDITOR.h"

#include <imgui.h>
#include <string>

class SphereTest : public MPE::Layer
{
  public:
    SphereTest();

    virtual ~SphereTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    void ToggleTransformSystem();

  private:
    MPE::SCOPE<std::string> m_LayerName;

    // Scene
    float m_clearColor[4];

    // Camera
    MPE::StaticOrthographicCamera m_mainCamera;

    // Sphere
    MPE::REF<MPE::ECS::ECS> m_ECS;
    MPE::REF<MPE::Sphere> m_sphere;
    glm::vec3 *m_sphereDeltaPosition;

    // ECS
    MPE::REF<MPE::ECS::TransformSystem> m_transformSystem;
    MPE::REF<MPE::ECS::RenderSystem> m_renderSystem;
    bool m_isTransformSystemActive = false;
};
