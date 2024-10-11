#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/IComponentPropertyEditor.h"
#include "Editor/Editor/ECS/Components/Meshes/Metadata/SphereMetadataComponent.h"
#include "Editor/Editor/ECS/ECS.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
class MPE_EDITOR_API SphereMetadataPropertiesEditor : public IComponentPropertyEditor
{
  public:
    SphereMetadataPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
    void Draw() override;
    bool IsModified() const override;
    void ApplyChanges() override;

  private:
    ECS::ECS& m_ECS;
    ECS::Entity m_entity;
    ECS::SphereMetadataComponent& m_metadata;
    float m_radius;
    uint32_t m_sectors;
    uint32_t m_stacks;
    bool m_smooth;
    unsigned char m_upAxis;
    bool m_isModified = false;
};
// {
//   public:
//     static void DrawSphereMetadataPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
// };
}