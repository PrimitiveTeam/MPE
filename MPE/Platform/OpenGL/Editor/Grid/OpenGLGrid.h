#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

#include "MPE/Editor/Grid/Grid.h"

#include "MPE/Renderer/Cameras/OrthographicCamera.h"
#include "MPE/Platform/OpenGL/Shaders/OpenGLShader.h"
#include "MPE/Platform/OpenGL/Pipeline/OpenGLVertexArray.h"

namespace MPE
{
class MPE_API OpenGLGrid : Grid
{
  public:
    OpenGLGrid();

    virtual ~OpenGLGrid() = default;

    virtual void Init(float gridSize, float gridSpacing, MPE::OrthographicCamera& camera) override;

    virtual void Resize(float gridSize, float gridSpacing) override;

    virtual void DrawGrid() override;

    virtual float GetGridSize() override { return gridSize; }

    virtual float GetGridSpacing() override { return gridSpacing; }

  private:
    // These cannot be 0 or less than 0, otherwise the grid will not be drawn and cause a freeze.
    float gridSize;
    float gridSpacing;

    MPE::REF<MPE::Shader> gridShader;
    MPE::REF<MPE::VertexArray> vertexArray;

    MPE::OrthographicCamera* mainCamera;
};
}