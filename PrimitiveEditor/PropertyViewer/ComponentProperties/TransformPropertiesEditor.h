#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/PropertyViewer/ComponentProperties/IComponentPropertyEditor.h"
#include "MPE/Editor/ECS/Components/Core/TransformComponent.h"
#include "MPE/Editor/ECS/ECS.h"

#include <glm/glm.hpp>

namespace MPE
{
class MPE_API TransformPropertiesEditor : public IComponentPropertyEditor
{
  public:
    TransformPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
    void Draw() override;
    bool IsModified() const override;
    void ApplyChanges() override;

  private:
    ECS::ECS& m_ECS;
    ECS::Entity m_entity;
    ECS::TransformComponent& m_transform;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    bool m_isModified = false;
};
// {
//   public:
//     static void DrawTransformPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
// };
}