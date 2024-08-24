#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/PropertyViewer/ComponentProperties/IComponentPropertyEditor.h"
#include "MPE/Editor/ECS/Components/Core/HierarchyComponent.h"
#include "MPE/Editor/ECS/ECS.h"

namespace MPE
{
class MPE_API HierarchyPropertiesEditor : public IComponentPropertyEditor
{
  public:
    HierarchyPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
    void Draw() override;
    bool IsModified() const override;
    void ApplyChanges() override;

  private:
    ECS::ECS& m_ECS;
    ECS::Entity m_entity;
    ECS::HierarchyComponent& m_hierarchy;
    REF<Object> m_parent;
    REF<Object> m_child;
    bool m_isModified = false;
};
}