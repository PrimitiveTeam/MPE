#pragma once

#include "MPE.h"
#include "MPEEDITOR.h"
#include "MPEECS.h"

#include <imgui.h>
#include <string>

class SimpleTriangleTest : public MPE::Layer
{
  public:
    SimpleTriangleTest();

    virtual ~SimpleTriangleTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    MPE::SCOPE<std::string> m_LayerName;

    // Scene
    float CLEAR_COLOR[4];

    MPE::REF<MPE::ECS::ECS> m_ECS;

    // Camera
    MPE::REF<MPE::OrthographicCameraController> SYS_CAMERA_CONTROLLER;

    // Triangle
    MPE::REF<MPE::Shader> SYS_Shader;
    MPE::REF<MPE::VertexArray> SYS_VertexArray;

    glm::vec3 TRIANGLE_POSITION;
    float TRIANGLE_SCALE_FACTOR;
    glm::vec3 TRIANGLE_VECTOR_SCALE;
    glm::mat4 TRIANGLE_SCALE;
};
