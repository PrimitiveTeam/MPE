#pragma once

#include "MPE.h"
#include "MPEEDITOR.h"
#include "MPEECS.h"

#include <imgui.h>
#include <string>

class TriangleTransformationTest : public MPE::Layer
{
  public:
    TriangleTransformationTest();

    virtual ~TriangleTransformationTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    void UpdateColor(MPE::Time deltaTime);
    void UpdateRotation(MPE::Time deltaTime);
    void ComputeTriangleScale();

  private:
    MPE::SCOPE<std::string> m_LayerName;

    // Scene
    float CLEAR_COLOR[4];

    MPE::REF<MPE::ECS::ECS> m_ECS;

    // Camera
    MPE::REF<MPE::Camera> SYS_CAMERA_CONTROLLER;

    // Triangle
    MPE::REF<MPE::Shader> SYS_Shader;
    MPE::REF<MPE::VertexArray> SYS_VertexArray;

    glm::vec3 TRIANGLE_POSITION;
    float TRIANGLE_SCALE_FACTOR;
    glm::vec3 TRIANGLE_VECTOR_SCALE;
    glm::mat4 TRIANGLE_SCALE;
    float TRIANGLE_COLOR[4];

    // Color Animation
    float incrementValue = 0.5f;
    bool br = true;
    bool bg = true;
    bool bb = true;
    float incrR, incrG, incrB;

    float settime = 0.0f;
    bool istimeset = false;

    // Rotation Animation
    bool autorotate;
    int rotatespeed;
    float rpm;
    float radians;
};
