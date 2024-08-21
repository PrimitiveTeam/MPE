#pragma once

#include "MPE.h"
#include "MPEECS.h"

#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#include <imgui.h>
#include <string>

class SimpleEcsTest : public MPE::Layer
{
  public:
    SimpleEcsTest();

    virtual ~SimpleEcsTest() = default;

    virtual void OnUpdate(MPE::Time deltaTime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    void UpdateRotation(MPE::Time deltaTime);

  private:
    MPE::SCOPE<std::string> m_LayerName;

    // ECS
    MPE::ECS::EntityManager m_entityManager;
    MPE::ECS::ComponentManager m_componentManager;
    MPE::ECS::SystemManager m_systemManager;
    MPE::ECS::Entity m_entity;
    std::shared_ptr<MPE::ECS::TranslationSystem> m_translationSystem;

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

    // Shader Library
    MPE::ShaderLibrary SYS_SHADER_LIBRARY;

    // Rotation Animation
    bool autorotate;
    int rotatespeed;
    float angleX, angleY, angleZ;
};
