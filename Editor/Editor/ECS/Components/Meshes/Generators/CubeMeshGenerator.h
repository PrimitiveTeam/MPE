#pragma once

#include "MPE/Core/_CORE.h"

#include <vector>

namespace MPE
{
namespace ECS
{
class MPE_EDITOR_API CubeMeshGenerator
{
  public:
    static void GenerateCube(unsigned int& stride, std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& textureCoordinates,
                             std::vector<float>& interleavedVertices, std::vector<unsigned int>& indices);
};
}
}