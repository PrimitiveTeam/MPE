#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

#include "MPE/Editor/Grid/Grid.h"

#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "Platform/OpenGLES/Shaders/OpenGLESShader.h"
#include "Platform/OpenGLES/Pipeline/OpenGLESVertexArray.h"

namespace MPE
{
class MPE_API OpenGLESGrid : Grid
{
  public:
    OpenGLESGrid();

    virtual ~OpenGLESGrid() = default;

    virtual void Init(float gridSize, float gridSpacing, MPE::OrthographicCamera& camera) override;

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

    MPE::OrthographicCamera* m_mainCamera;
};
}