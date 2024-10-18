#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"

namespace MPE
{
class Camera;
class MPE_EDITOR_API Grid
{
  public:
    Grid();
    virtual ~Grid() = default;

    virtual void Init(float gridSize, float gridSpacing, REF<Camera> camera) = 0;

    virtual void Resize(float gridSize, float gridSpacing) = 0;

    virtual void DrawGrid() = 0;

    virtual float GetGridSize() = 0;

    virtual float GetGridSpacing() = 0;
};
}