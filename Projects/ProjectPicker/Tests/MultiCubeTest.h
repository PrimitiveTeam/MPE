#pragma once

#include "MPE.h"
#include "MPEECS.h"
#include "MPEEDITOR.h"

#include <imgui.h>
#include <string>
#include <vector>

class MultiCubeTest : public MPE::Layer
{
  public:
    MultiCubeTest();

    virtual ~MultiCubeTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    void ToggleTransformSystem();
    void IterativeRotate(MPE::Time deltaTime);

  private:
    MPE::SCOPE<std::string> m_LayerName;

    // Scene
    float m_clearColor[4];

    // Camera
    MPE::StaticOrthographicCamera m_mainCamera;

    // Cube
    MPE::REF<MPE::ECS::ECS> m_ECS;
    std::vector<MPE::REF<MPE::Cube>> m_cubes;
    glm::vec3 *m_cubeDeltaPosition;
    glm::vec3 *m_cubeDeltaRotation;

    // ECS
    MPE::REF<MPE::ECS::TransformSystem> m_transformSystem;
    bool m_isTransformSystemActive = false;
};
