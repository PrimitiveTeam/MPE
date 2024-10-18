#pragma once

#include "MPE.h"
#include "MPEEDITOR.h"
#include "MPEECS.h"

#include <imgui.h>
#include <string>

class SimpleLightingTest : public MPE::Layer
{
  public:
    SimpleLightingTest();

    virtual ~SimpleLightingTest() = default;

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

    MPE::REF<MPE::ECS::ECS> m_ECS;

    // Camera
    MPE::REF<MPE::PerspectiveCamera> m_perspectiveCamera;
    // float m_fov;
    // float m_near;
    // float m_far;

    // Rectangle 1
    MPE::REF<MPE::VertexArray> m_vertexArray;

    glm::vec3 m_rectanglePosition;
    float m_rectangleScaleFactor;
    glm::vec3 m_rectangleVectorScale;
    glm::mat4 m_rectangleScale;
    float m_rectangleColor[4];

    // Rectangle 1
    MPE::REF<MPE::VertexArray> m_vertexArray2;

    glm::vec3 m_rectanglePosition2;
    float m_rectangleScaleFactor2;
    glm::vec3 m_rectangleVectorScale2;
    glm::mat4 m_rectangleScale2;
    float m_rectangleColor2[4];

    // Rotation Animation Rectangle 1
    bool m_autoRotate;
    int m_rotateSpeed;
    float m_angleX, m_angleY, m_angleZ;

    // Rotation Animation Rectangle 2
    bool m_autoRotate2;
    int m_rotateSpeed2;
    float m_angleX2, m_angleY2, m_angleZ2;

    // Lighting
    MPE::REF<MPE::VertexArray> m_lightVertexArray;
    glm::vec3 m_lightPosition;
    float m_lightColor[4];
};
