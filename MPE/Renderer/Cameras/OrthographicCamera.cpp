#include "OrthographicCamera.h"
#include "MPE/MPEPCH.h"

#include "MPE/Log/GlobalLog.h"

#include <glm/gtc/matrix_transform.hpp>

namespace MPE
{
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : PROJECTION_MATRIX(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), VIEW_MATRIX(1.0f)
{
    MPE_INFO("Orthographic Camera Created: {0}, {1}, {2}, {3}, {4}, {5}", left, right, bottom, top, -1.0f, 1.0f);
    PROJECTION_VIEW_MATRIX = PROJECTION_MATRIX * VIEW_MATRIX;
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
    MPE_INFO("Orthographic Camera Projection set: {0}, {1}, {2}, {3}", left, right, bottom, top);
    PROJECTION_MATRIX = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    PROJECTION_VIEW_MATRIX = PROJECTION_MATRIX * VIEW_MATRIX;
}

void OrthographicCamera::COMPUTE_VIEW_MATRIX()
{
    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), CAMERA_POSITION) * glm::rotate(glm::mat4(1.0f), glm::radians(CAMERA_Z_AXIS_ROTATION), glm::vec3(0, 0, 1));

    VIEW_MATRIX = glm::inverse(transform);

    PROJECTION_VIEW_MATRIX = PROJECTION_MATRIX * VIEW_MATRIX;
}

void OrthographicCamera::SetPosition(const glm::vec3 &position)
{
    CAMERA_POSITION = position;
    COMPUTE_VIEW_MATRIX();
}
void OrthographicCamera::SetRotation(float rotation)
{
    CAMERA_Z_AXIS_ROTATION = rotation;
    COMPUTE_VIEW_MATRIX();
}
}