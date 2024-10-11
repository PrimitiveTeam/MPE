#pragma once

#include "MPE/Core/_CORE.h"

#include <vector>

namespace MPE
{
namespace ECS
{
struct MeshComponent;
class SphereMetadataComponent;
struct RenderComponent;

class MPE_EDITOR_API SphereMeshGenerator
{
  public:
    static void RegenerateRenderComponent(MeshComponent& mesh, SphereMetadataComponent& metadata, RenderComponent& renderComp);

    static void GenerateSphere(float radius, uint32_t sectors, uint32_t stacks, bool smooth, unsigned char upAxis, unsigned int& stride,
                               std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& textureCoordinates,
                               std::vector<float>& interleavedVertices, std::vector<float>& indicesLines, std::vector<unsigned int>& indices);

    static void SwitchUpAxis(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& interleavedVertices, unsigned int from,
                             unsigned int to);

    static void SwitchSmoothness(float radius, unsigned char upAxis, uint32_t sectors, uint32_t stacks, std::vector<float>& vertices,
                                 std::vector<float>& normals, std::vector<float>& textureCoordinates, std::vector<float>& interleavedVertices,
                                 std::vector<float>& indicesLines, std::vector<unsigned int>& indices, bool smooth);

    static void ReverseNormals(std::vector<float>& normals, std::vector<float>& interleavedVertices, std::vector<unsigned int>& indices);

  private:
    static void GenerateSmoothVertices(float radius, uint32_t sectors, uint32_t stacks, std::vector<float>& vertices, std::vector<float>& normals,
                                       std::vector<float>& textureCoordinates, std::vector<float>& indicesLines, std::vector<unsigned int>& indices);

    static void GenerateFlatVertices(float radius, uint32_t sectors, uint32_t stacks, std::vector<float>& vertices, std::vector<float>& normals,
                                     std::vector<float>& textureCoordinates, std::vector<float>& indicesLines, std::vector<unsigned int>& indices);

    static std::vector<float> GenerateFaceNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

    static void GenerateInterleavedVertices(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& textureCoordinates,
                                            std::vector<float>& interleavedVertices);

    static void AddVertex(std::vector<float>& vertices, float x, float y, float z);

    static void AddNormal(std::vector<float>& normals, float nx, float ny, float nz);

    static void AddTexureCoord(std::vector<float>& textureCoordinates, float s, float t);

    static void AddIndices(std::vector<unsigned int>& indices, unsigned int i1, unsigned int i2, unsigned int i3);
};
}
}