#include "PerspectiveCamera.h"
#include "MPE/MPEPCH.h"

#include "MPE/Log/GlobalLog.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
PerspectiveCamera::PerspectiveCamera(ECS::ECS& ecs) : Camera(ecs)
{
    // m_cameraComponent = &m_ECS.AddComponentToEntity<ECS::PerspectiveCameraComponent>(m_entity, 45.0f, 1.0f, 0.1f, 100.0f);
    m_cameraComponent = m_ECS.AddComponentToEntity(m_entity, NEWREF<ECS::PerspectiveCameraComponent>(45.0f, 1.0f, 0.1f, 100.0f));

    Init();
}

PerspectiveCamera::PerspectiveCamera(ECS::ECS& ecs, float fov, float aspectRatio, float nearClip, float farClip) : Camera(ecs)
{
    // m_cameraComponent = &m_ECS.AddComponentToEntity<ECS::PerspectiveCameraComponent>(m_entity, fov, aspectRatio, nearClip, farClip);
    m_cameraComponent = m_ECS.AddComponentToEntity(m_entity, NEWREF<ECS::PerspectiveCameraComponent>(fov, aspectRatio, nearClip, farClip));

    Init();
}

void PerspectiveCamera::Init() {}

void PerspectiveCamera::OnUpdate(Time deltaTime) {}

void PerspectiveCamera::OnRender(Camera& camera) {}

void PerspectiveCamera::OnImGuiRender() {}

void PerspectiveCamera::OnEvent(Event& event) {}
}