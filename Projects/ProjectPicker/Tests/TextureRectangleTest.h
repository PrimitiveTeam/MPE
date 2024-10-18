#pragma once

#include "MPE.h"
#include "MPEEDITOR.h"
#include "MPEECS.h"

#include <imgui.h>
#include <string>

class TextureRectangleTest : public MPE::Layer
{
  public:
    TextureRectangleTest();

    virtual ~TextureRectangleTest() = default;

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
    MPE::REF<MPE::Camera> SYS_CAMERA_CONTROLLER;

    // Rectangle
    MPE::REF<MPE::Shader> SYS_Shader;
    MPE::REF<MPE::VertexArray> SYS_VertexArray;

    glm::vec3 RECTANGLE_POSITION;
    float RECTANGLE_SCALE_FACTOR;
    glm::vec3 RECTANGLE_VECTOR_SCALE;
    glm::mat4 RECTANGLE_SCALE;

    // TEXTURES;
    MPE::REF<MPE::Texture2D> TEST_TEXTURE;
};
