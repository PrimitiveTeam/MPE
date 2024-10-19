#pragma once

#include "MPE/Core/_CORE.h"

#include <vector>

namespace MPE
{
namespace ECS
{
struct MeshComponent;
class GridMetadataComponent;
struct RenderComponent;

class MPE_EDITOR_API GridMeshGenerator
{
  public:
    static void RegenerateRenderComponent(MeshComponent& mesh, GridMetadataComponent& metadata, RenderComponent& renderComp);

    static void GenerateGrid(float gridSize, float gridSpacing, unsigned int& stride, std::vector<float>& vertices, std::vector<float>& normals,
                             std::vector<float>& textureCoordinates, std::vector<float>& interleavedVertices, std::vector<float>& indicesLines, std::vector<unsigned int>& indices);
};
}
}