#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

#include "MPE/Renderer/Cameras/OrthographicCamera.h"

namespace MPE
{
class MPE_EDITOR_API Grid
{
  public:
    Grid();
    virtual ~Grid() = default;

    virtual void Init(float gridSize, float gridSpacing, MPE::OrthographicCamera& camera) = 0;

    virtual void Resize(float gridSize, float gridSpacing) = 0;

    virtual void DrawGrid() = 0;

    virtual float GetGridSize() = 0;

    virtual float GetGridSpacing() = 0;
};
}