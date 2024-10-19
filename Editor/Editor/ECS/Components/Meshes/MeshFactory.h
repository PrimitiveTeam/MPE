#pragma once

#include "MPE/Core/_CORE.h"
#include "MeshComponent.h"

// Mesh Metadata
#include "Metadata/SphereMetadataComponent.h"
#include "Metadata/GridMetadataComponent.h"

namespace MPE
{
namespace ECS
{
class MPE_EDITOR_API MeshFactory
{
  public:
    // Cube generation (no additional params)
    static MeshComponent CreateCube();

    // Sphere generation (with sphere-specific parameters)
    static std::pair<MeshComponent, SphereMetadataComponent> CreateSphere(float radius = 1.0f, uint32_t sectors = 36, uint32_t stacks = 18, bool smooth = true,
                                                                          uint32_t upAxis = 3);

    static std::pair<MeshComponent, GridMetadataComponent> CreateGrid(float gridSize = 10.0f, float gridSpacing = 1.0f);
};
}
}
