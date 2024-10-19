#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/ECS/ECS.h"

// Mesh Generators
#include "Generators/CubeMeshGenerator.h"
// #include "Generators/SphereMeshGenerator.h"

#include "MPE/Log/GlobalLog.h"

namespace MPE
{
enum class MPE_EDITOR_API MeshType
{
    Cube,
    Sphere,
    Grid,
    Custom
};

static std::string MeshTypeToString(MeshType type)
{
    switch (type)
    {
        case MeshType::Cube:
            return "Cube";
        case MeshType::Sphere:
            return "Sphere";
        case MeshType::Grid:
            return "Grid";
        case MeshType::Custom:
            return "Custom";
    }
    return "Unknown";
}

namespace ECS
{
struct MPE_EDITOR_API MeshComponent
{
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> textureCoords;
    std::vector<float> interleavedVertices;
    std::vector<float> indicesLines;
    std::vector<unsigned int> indices;
    unsigned int stride;
    MeshType meshType;
    bool lineDrawing = false;
};
}
}