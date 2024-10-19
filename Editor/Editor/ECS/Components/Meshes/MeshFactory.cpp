#include "MeshFactory.h"

#include "MPE/Core/_CORE.h"

// Mesh Generators
#include "Generators/CubeMeshGenerator.h"
#include "Generators/SphereMeshGenerator.h"
#include "Generators/GridMeshGenerator.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
namespace ECS
{
// Cube generation (no additional params)
MeshComponent MeshFactory::CreateCube()
{
    MeshComponent mesh;
    mesh.meshType = MeshType::Cube;
    CubeMeshGenerator::GenerateCube(mesh.stride, mesh.vertices, mesh.normals, mesh.textureCoords, mesh.interleavedVertices, mesh.indices);
    return mesh;
}

// Sphere generation (with sphere-specific parameters)
std::pair<MeshComponent, SphereMetadataComponent> MeshFactory::CreateSphere(float radius, uint32_t sectors, uint32_t stacks, bool smooth, uint32_t upAxis)
{
    MeshComponent mesh;
    mesh.meshType = MeshType::Sphere;
    SphereMetadataComponent metadata(radius, sectors, stacks, smooth, upAxis);

    SphereMeshGenerator::GenerateSphere(metadata.GetRadius(), metadata.GetSectors(), metadata.GetStacks(), metadata.GetSmooth(), metadata.GetUpAxis(),
                                        mesh.stride, mesh.vertices, mesh.normals, mesh.textureCoords, mesh.interleavedVertices, mesh.indicesLines,
                                        mesh.indices);

    return std::make_pair(mesh, metadata);
}

std::pair<MeshComponent, GridMetadataComponent> MeshFactory::CreateGrid(float gridSize, float gridSpacing)
{
    MeshComponent mesh;
    mesh.meshType = MeshType::Grid;
    GridMetadataComponent metadata(gridSize, gridSpacing);

    GridMeshGenerator::GenerateGrid(metadata.GetGridSize(), metadata.GetGridSpacing(), mesh.stride, mesh.vertices, mesh.normals, mesh.textureCoords,
                                    mesh.interleavedVertices, mesh.indicesLines, mesh.indices);

    return std::make_pair(mesh, metadata);
}
}
}
