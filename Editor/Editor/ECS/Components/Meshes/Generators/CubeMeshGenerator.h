#pragma once

#include <vector>

namespace MPE
{
namespace ECS
{
class CubeMeshGenerator
{
  public:
    static void GenerateCube(unsigned int& stride, std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& textureCoordinates, std::vector<float>& interleavedVertices, std::vector<unsigned int>& indices);
};
}
}