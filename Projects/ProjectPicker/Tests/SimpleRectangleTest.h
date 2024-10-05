#pragma once

#include "MPE.h"

#include <imgui.h>
#include <string>

class SimpleRectangleTest : public MPE::Layer
{
  public:
    SimpleRectangleTest();

    virtual ~SimpleRectangleTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    MPE::SCOPE<std::string> m_LayerName;

    // Scene
    float CLEAR_COLOR[4];

    // Camera
    MPE::StaticOrthographicCamera SYS_CAMERA_CONTROLLER;

    // Rectangle
    MPE::REF<MPE::Shader> SYS_Shader;
    MPE::REF<MPE::VertexArray> SYS_VertexArray;

    glm::vec3 RECTANGLE_POSITION;
    float RECTANGLE_SCALE_FACTOR;
    glm::vec3 RECTANGLE_VECTOR_SCALE;
    glm::mat4 RECTANGLE_SCALE;
};
