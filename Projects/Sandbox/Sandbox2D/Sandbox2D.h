#pragma once

#include "MPE.h"

class Sandbox2D : public MPE::Layer
{
  private:
    MPE::REF<MPE::VertexArray> SYS_VertexArray;

    // MPE::ShaderLibrary SYS_SHADER_LIBRARY;
    MPE::REF<MPE::Shader> SYS_Shader;

    MPE::REF<MPE::Texture2D> TEST_TEXTURE;

    MPE::OrthographicCameraController SYS_CAMERA_CONTROLLER;

    glm::vec4 SQUARE_COLOR = {0.2f, 0.4f, 0.2f, 1.0f};

    float trans = 1.0f;

    glm::vec4 CLEAR_COLOR = {0.5f, 0.25f, 0.5f, 1.0f};

    // float CLEAR_COLOR[4] = {0.5f, 0.25f, 0.5f, 1.0f};

  public:
    Sandbox2D();

    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;

    virtual void OnDetach() override;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;
};