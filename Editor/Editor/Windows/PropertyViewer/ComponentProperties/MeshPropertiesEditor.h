#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/IComponentPropertyEditor.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshComponent.h"
#include "Editor/Editor/ECS/ECS.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
class MPE_EDITOR_API MeshPropertiesEditor : public IComponentPropertyEditor
{
  public:
    MeshPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
    void Draw() override;
    bool IsModified() const override;
    void ApplyChanges() override;

  private:
    ECS::ECS& m_ECS;
    ECS::Entity m_entity;
    ECS::MeshComponent& m_mesh;
    std::vector<float> m_vertices;
    std::vector<float> m_normals;
    std::vector<float> m_textureCoords;
    std::vector<unsigned int> m_indices;
    unsigned int m_stride;
    MeshType m_meshType;
    bool m_isModified = false;
};
// {
//   public:
//     static void DrawMeshPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
// };
}