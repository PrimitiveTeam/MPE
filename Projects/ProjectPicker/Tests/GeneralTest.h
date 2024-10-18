#pragma once

#include "MPE.h"
#include "MPEEDITOR.h"
#include "MPEECS.h"

#include <imgui.h>
#include <string>

class GeneralTest : public MPE::Layer
{
  public:
    GeneralTest();

    virtual ~GeneralTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

    void ComputeTriangleScale();

    void ComputeSquareScale();

  private:
    MPE::SCOPE<std::string> m_LayerName;
    // TRIANGLE
    MPE::REF<MPE::Shader> SYS_Shader;
    MPE::REF<MPE::VertexArray> SYS_VertexArray;

    // SQUARE
    MPE::REF<MPE::Shader> SYS_SQSH;
    MPE::REF<MPE::VertexArray> SYS_SQVA;

    // TEXTURES;
    MPE::REF<MPE::Texture2D> TEST_TEXTURE;
    MPE::REF<MPE::Texture2D> TEST_TEXTURE2;

    // SCENE
    float CLEAR_COLOR[4];

    MPE::REF<MPE::ECS::ECS> m_ECS;

    // Camera
    MPE::REF<MPE::OrthographicCameraController> SYS_CAMERA_CONTROLLER;

    // TRANSFORM
    float OBJECT_MOVEMENT_SPEED = 0.75f;
    float OBJECT_ROTATION_SPEED = 25.0f;

    // TRIANGLE
    glm::vec3 TRIANGLE_POSITION;
    float TRIANGLE_SCALE_FACTOR;
    glm::vec3 TRIANGLE_VECTOR_SCALE;
    glm::mat4 TRIANGLE_SCALE;

    // SQUARE
    glm::vec3 SQ_POSITION;
    float SQ_SCALE_FACTOR;
    glm::vec3 SQ_VECTOR_SCALE;
    glm::mat4 SQ_SCALE;
    // SQUARES COLOR
    float COL_1[4] = {1.0f, 0.2f, 0.2f, 1.0f};
    glm::vec4 COL_2 = {0.2f, 0.4f, 0.2f, 1.0f};

    // IMGUI
    bool SHOW_TRANSFORM[2] = {false};
    bool KEY_CONTROL_TRANSFORM[2] = {false};
};
