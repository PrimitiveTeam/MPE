#pragma once

#include "MPE.h"
#include "MPEECS.h"
#include "MPEEDITOR.h"

#include <imgui.h>
#include <string>

class CubeAbstractionTest : public MPE::Layer
{
  public:
    CubeAbstractionTest();

    virtual ~CubeAbstractionTest() = default;

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

    // Cube
    MPE::REF<MPE::ECS::ECS> m_ECS;
    MPE::REF<MPE::Cube> m_cube;
    glm::vec3 *m_cubeDeltaPosition;

    // ECS
    MPE::REF<MPE::ECS::TransformSystem> m_transformSystem;
    bool m_isTransformSystemActive = false;
};
