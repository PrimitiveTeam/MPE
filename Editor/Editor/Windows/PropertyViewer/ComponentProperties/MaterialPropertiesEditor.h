#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/IComponentPropertyEditor.h"
#include "Editor/Editor/ECS/Components/Graphical/MaterialComponent.h"
#include "Editor/Editor/ECS/ECS.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
class MPE_EDITOR_API MaterialPropertiesEditor : public IComponentPropertyEditor
{
  public:
    MaterialPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
    void Draw() override;
    bool IsModified() const override;
    void ApplyChanges() override;

  private:
    ECS::ECS& m_ECS;
    ECS::Entity m_entity;
    ECS::MaterialComponent& m_material;
    glm::vec4 m_color;
    bool m_isModified = false;
};
// {
//   public:
//     static void DrawMaterialPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
// };
}