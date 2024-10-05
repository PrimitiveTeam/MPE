#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/IComponentPropertyEditor.h"
#include "Editor/Editor/ECS/Components/Core/TagComponent.h"
#include "Editor/Editor/ECS/ECS.h"

namespace MPE
{
class MPE_EDITOR_API TagPropertiesEditor : public IComponentPropertyEditor
{
  public:
    TagPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
    void Draw() override;
    bool IsModified() const override;
    void ApplyChanges() override;

  private:
    ECS::ECS& m_ECS;
    ECS::Entity m_entity;
    ECS::TagComponent& m_tag;
    std::string m_name;
    std::string m_tagName;
    bool m_isModified = false;
};
}