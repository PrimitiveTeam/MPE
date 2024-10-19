#include "GridMeshGenerator.h"

#include "MPE/Log/GlobalLog.h"

#include "Editor/Editor/Ecs/Components/Meshes/MeshComponent.h"
#include "Editor/Editor/Ecs/Components/Meshes/Metadata/SphereMetadataComponent.h"
#include "Editor/Editor/Ecs/Components/Graphical/RenderComponent.h"

namespace MPE
{
namespace ECS
{
void GridMeshGenerator::RegenerateRenderComponent(MeshComponent& mesh, GridMetadataComponent& metadata, RenderComponent& renderComp)
{
    // REF<VertexBuffer> vertexBuffer = VertexBuffer::Create(mesh.interleavedVertices.data(), mesh.interleavedVertices.size() * sizeof(float));
    REF<VertexBuffer> vertexBuffer = VertexBuffer::Create(mesh.vertices.data(), mesh.vertices.size() * sizeof(float));
    vertexBuffer->SetLayout({{ShaderDataType::Vec3, "ATTR_POS"}});
    renderComp.vertexArray->AddVertexBuffer(vertexBuffer);

    REF<IndexBuffer> indexBuffer = IndexBuffer::Create(mesh.indices.data(), mesh.indices.size());
    renderComp.vertexArray->SetIndexBuffer(indexBuffer);
}

void GridMeshGenerator::GenerateGrid(float gridSize, float gridSpacing, unsigned int& stride, std::vector<float>& vertices, std::vector<float>& normals,
                                     std::vector<float>& textureCoordinates, std::vector<float>& interleavedVertices, std::vector<float>& indicesLines,
                                     std::vector<unsigned int>& indices)
{
    MPE_ASSERT(gridSize > 0, "Grid size must be greater than 0.");
    MPE_ASSERT(gridSpacing > 0, "Grid spacing must be greater than 0.");

    // clean all vectors
    vertices.clear();
    normals.clear();
    textureCoordinates.clear();
    interleavedVertices.clear();
    indicesLines.clear();
    indices.clear();
    stride = 0;

    // ATTR_POS (VEC3)
    stride += 12;

    unsigned int index = 0;

    for (float i = -gridSize; i <= gridSize; i += gridSpacing)
    {
        vertices.push_back(i);
        vertices.push_back(-gridSize);
        vertices.push_back(0.0f);

        vertices.push_back(i);
        vertices.push_back(gridSize);
        vertices.push_back(0.0f);

        indicesLines.push_back(index);
        indicesLines.push_back(index + 1);
        indices.push_back(index);
        indices.push_back(index + 1);
        index += 2;

        vertices.push_back(-gridSize);
        vertices.push_back(i);
        vertices.push_back(0.0f);

        vertices.push_back(gridSize);
        vertices.push_back(i);
        vertices.push_back(0.0f);

        indicesLines.push_back(index);
        indicesLines.push_back(index + 1);
        indices.push_back(index);
        indices.push_back(index + 1);
        index += 2;
    }

    // Make interleaved vertices
    for (size_t i = 0; i < vertices.size() / 3; i++)
    {
        // Vertex positions
        interleavedVertices.push_back(vertices[i * 3 + 0]);
        interleavedVertices.push_back(vertices[i * 3 + 1]);
        interleavedVertices.push_back(vertices[i * 3 + 2]);
    }
}
}
}