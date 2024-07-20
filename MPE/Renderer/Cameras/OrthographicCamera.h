#pragma once

#include "MPE/Core/_CORE.h"

#include <glm/glm.hpp>

namespace MPE
{
class MPE_API OrthographicCamera
{
  public:
    // float near, float far
    OrthographicCamera(float left, float right, float bottom, float top);
    void SetProjection(float left, float right, float bottom, float top);

    void SetPosition(const glm::vec3 &position);
    void SetRotation(float rotation);

    const glm::vec3 &GetPosition() const { return CAMERA_POSITION; }
    // get position but allow to modify it
    glm::vec3 &ManipulatePosition() { return CAMERA_POSITION; }
    float GetRotation() const { return CAMERA_Z_AXIS_ROTATION; }

    const glm::mat4 &GetProjectionMatrix() const { return PROJECTION_MATRIX; }
    const glm::mat4 &GetViewMatrix() const { return VIEW_MATRIX; }
    const glm::mat4 &GetProjectionViewMatrix() const { return PROJECTION_VIEW_MATRIX; }

  private:
    glm::mat4 PROJECTION_MATRIX;
    glm::mat4 VIEW_MATRIX;
    glm::mat4 PROJECTION_VIEW_MATRIX;

    glm::vec3 CAMERA_POSITION = {0.0f, 0.0f, 0.0f};
    float CAMERA_Z_AXIS_ROTATION = 0.0f;

    void COMPUTE_VIEW_MATRIX();
};
}