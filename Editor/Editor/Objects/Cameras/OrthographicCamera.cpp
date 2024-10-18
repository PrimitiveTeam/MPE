#include "OrthographicCamera.h"
#include "MPE/MPEPCH.h"

#include "MPE/Log/GlobalLog.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
OrthographicCamera::OrthographicCamera(ECS::ECS& ecs) : Camera(ecs)
{
    // m_cameraComponent = &m_ECS.AddComponentToEntity<ECS::OrthographicCameraComponent>(m_entity, -1.0f, 1.0f, -1.0f, 1.0f);
    m_cameraComponent = m_ECS.AddComponentToEntity(m_entity, NEWREF<ECS::OrthographicCameraComponent>(-1.0f, 1.0f, -1.0f, 1.0f));

    Init();
}

OrthographicCamera::OrthographicCamera(ECS::ECS& ecs, float left, float right, float bottom, float top) : Camera(ecs)
{
    // m_cameraComponent = &m_ECS.AddComponentToEntity<ECS::OrthographicCameraComponent>(m_entity, left, right, bottom, top);
    m_cameraComponent = m_ECS.AddComponentToEntity(m_entity, NEWREF<ECS::OrthographicCameraComponent>(left, right, bottom, top));

    Init();
}

void OrthographicCamera::Init() {}

void OrthographicCamera::OnUpdate(Time deltaTime) {}

void OrthographicCamera::OnRender(Camera& camera) {}

void OrthographicCamera::OnImGuiRender() {}

void OrthographicCamera::OnEvent(Event& event) {}
}