#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"
#include "MPE/Vendor/GLM/GLM.h"
#include "CameraComponent.h"

namespace MPE
{
namespace ECS
{
class MPE_EDITOR_API OrthographicCameraComponent : public CameraComponent
{
  public:
    // float near, float far
    OrthographicCameraComponent(float left, float right, float bottom, float top);

    ~OrthographicCameraComponent() = default;

    void SetProjection(float left, float right, float bottom, float top);

    virtual void SetAspectRatio(float aspectRatio) override final;
};
}
}