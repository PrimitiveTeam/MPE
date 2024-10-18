#pragma once

#include "MPE.h"
#include "MPEEDITOR.h"
#include "MPEECS.h"

class TexturesTest : public MPE::Layer
{
  private:
    MPE::REF<MPE::VertexArray> SYS_VertexArray;

    // MPE::ShaderLibrary SYS_SHADER_LIBRARY;
    MPE::REF<MPE::Shader> SYS_Shader;

    MPE::REF<MPE::Texture2D> TEST_TEXTURE;

    MPE::REF<MPE::ECS::ECS> m_ECS;

    // Camera
    MPE::REF<MPE::OrthographicCameraController> SYS_CAMERA_CONTROLLER;

    glm::vec4 SQUARE_COLOR = {0.2f, 0.4f, 0.2f, 1.0f};

    float trans = 1.0f;

    glm::vec4 CLEAR_COLOR = {0.5f, 0.25f, 0.5f, 1.0f};

    // float CLEAR_COLOR[4] = {0.5f, 0.25f, 0.5f, 1.0f};

  public:
    TexturesTest();

    virtual ~TexturesTest() = default;

    virtual void OnAttach() override;

    virtual void OnDetach() override;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;
};