#pragma once

#include "MPE.h"

#include <imgui.h>
#include <string>

class SimplePerspectiveCameraTest : public MPE::Layer
{
  public:
    SimplePerspectiveCameraTest();

    virtual ~SimplePerspectiveCameraTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    void UpdateRotation(MPE::Time deltaTime);

  private:
    MPE::SCOPE<std::string> m_layerName;

    // Scene
    float m_clearColor[4];

    // Camera
    MPE::PerspectiveCamera m_perspectiveCamera;
    // float m_fov;
    // float m_near;
    // float m_far;

    // Rectangle
    MPE::REF<MPE::Shader> m_shader;
    MPE::REF<MPE::VertexArray> m_vertexArray;

    glm::vec3 m_rectanglePosition;
    float m_rectangleScaleFactor;
    glm::vec3 m_rectangleVectorScale;
    glm::mat4 m_rectangleScale;
    float m_rectangleColor[4];

    // Rotation Animation
    bool m_autoRotate;
    int m_rotateSpeed;
    float m_angleX, m_angleY, m_angleZ;
};
