#include "MPE/Core/_CORE.h"
#include "MeshComponent.h"
#include "MeshFactory.h"
// Metadata
#include "Metadata/MeshMetadata.h"
// Sphere
#include "Metadata/SphereMetadataComponent.h"
#include "Generators/SphereMeshGenerator.h"
#include "Editor/Editor/Ecs/Components/Graphical/RenderComponent.h"

namespace MPE
{
namespace ECS
{
template <typename MetadataType>
static void RegenerateMeshIfDirty(MeshComponent& mesh, MetadataType& metadata, RenderComponent& renderComp)
{
    if (metadata.IsDirty())
    {
        if constexpr (std::is_same_v<MetadataType, SphereMetadataComponent>)
        {
            // Depending on the data dirtied, we either regenerate the whole mesh, switch the up axis, change the smoothness, or reverse the normals

            if (metadata.IsBaseDirty())
            {
                SphereMeshGenerator::GenerateSphere(metadata.GetRadius(), metadata.GetSectors(), metadata.GetStacks(), metadata.GetSmooth(),
                                                    metadata.GetUpAxis(), mesh.stride, mesh.vertices, mesh.normals, mesh.textureCoords,
                                                    mesh.interleavedVertices, mesh.indicesLines, mesh.indices);
            }
            if (metadata.IsUpAxisDirty())
            {
                SphereMeshGenerator::SwitchUpAxis(mesh.vertices, mesh.normals, mesh.interleavedVertices, metadata.GetPreviousUpAxis(), metadata.GetUpAxis());
                metadata.ResetPreviousUpAxis();
            }
            if (metadata.IsSmoothDirty())
            {
                SphereMeshGenerator::SwitchSmoothness(metadata.GetRadius(), metadata.GetUpAxis(), metadata.GetSectors(), metadata.GetStacks(), mesh.vertices,
                                                      mesh.normals, mesh.textureCoords, mesh.interleavedVertices, mesh.indicesLines, mesh.indices,
                                                      metadata.GetSmooth());
            }
            if (metadata.IsReverseNormals())
            {
                SphereMeshGenerator::ReverseNormals(mesh.normals, mesh.interleavedVertices, mesh.indices);
            }

            SphereMeshGenerator::RegenerateRenderComponent(mesh, metadata, renderComp);
        }

        metadata.ClearAllDirty();
    }
}
}
}
