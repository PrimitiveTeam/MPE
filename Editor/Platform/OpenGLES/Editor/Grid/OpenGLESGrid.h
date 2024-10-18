#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

#include "Editor/Editor/Grid/Grid.h"

#include "Platform/OpenGLES/Shaders/OpenGLESShader.h"
#include "Platform/OpenGLES/Pipeline/OpenGLESVertexArray.h"

namespace MPE
{
class Camera;

class MPE_EDITOR_API OpenGLESGrid : public Grid
{
  public:
    OpenGLESGrid();

    virtual ~OpenGLESGrid() = default;

    virtual void Init(float gridSize, float gridSpacing, REF<Camera> camera) override;

    virtual void Resize(float gridSize, float gridSpacing) override;

    virtual void DrawGrid() override;

    virtual float GetGridSize() override { return m_size; }

    virtual float GetGridSpacing() override { return m_spacing; }

  private:
    // These cannot be 0 or less than 0, otherwise the grid will not be drawn and cause a freeze.
    float m_size;
    float m_spacing;

    MPE::REF<MPE::Shader> m_shader;
    MPE::REF<MPE::VertexArray> m_vertexArray;

    REF<Camera> m_mainCamera;
};
}