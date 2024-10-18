#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"
#include "MPE/Vendor/GLM/GLM.h"
#include "Editor/Editor/ECS/Components/Cameras/OrthographicCameraComponent.h"
#include "CameraControllerComponent.h"

namespace MPE
{
namespace ECS
{
class MPE_EDITOR_API OrthographicCameraControllerComponent : public CameraControllerComponent
{
  public:
    OrthographicCameraControllerComponent(REF<OrthographicCameraComponent> cameraComponent)
        : CameraControllerComponent(cameraComponent), m_orthographicCameraComponent(cameraComponent)
    {
    }

    ~OrthographicCameraControllerComponent() = default;

    // virtual void OnEvent(Event &e) override final
    // {
    //     EventDispatcher dispatcher(e);
    //     dispatcher.Dispatch<MouseScrolledEvent>(MPE_BIND_EVENT_FUNCTION(OrthographicCameraControllerComponent::OnMouseScrolled));
    //     dispatcher.Dispatch<WindowResizeEvent>(MPE_BIND_EVENT_FUNCTION(OrthographicCameraControllerComponent::OnWindowResized));
    // }

    virtual void SetZoomLevel(float zoom) override final
    {
        if (zoom < m_maxZoomLevel)
        {
            MPE_CORE_WARN("ZOOM LEVEL {0}f IS BELOW MAXIMUM ALLOWED {1}", zoom, m_maxZoomLevel);
            return;
        }
        else
        {
            m_zoomLevel = zoom;
            auto aspectRation = m_orthographicCameraComponent->GetAspectRatio();
            m_orthographicCameraComponent->SetProjection(-aspectRation * m_zoomLevel, aspectRation * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
        }
    }

  protected:
    // virtual bool OnMouseScrolled(MouseScrolledEvent &e) override final
    // {
    //     m_zoomLevel -= e.GetYOffset() * m_cameraZoomSpeed;
    //     m_zoomLevel = std::max(m_zoomLevel, m_maxZoomLevel);
    //     auto aspectRation = m_orthographicCameraComponent->GetAspectRatio();
    //     m_orthographicCameraComponent->SetProjection(-aspectRation * m_zoomLevel, aspectRation * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
    //     return false;
    // }

    // virtual bool OnWindowResized(WindowResizeEvent &e) override final
    // {
    //     float aspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
    //     m_orthographicCameraComponent->SetAspectRatio(aspectRatio);
    //     m_orthographicCameraComponent->SetProjection(-aspectRatio * m_zoomLevel, aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
    //     return false;
    // }

  protected:
    REF<OrthographicCameraComponent> m_orthographicCameraComponent = nullptr;
};
}
}