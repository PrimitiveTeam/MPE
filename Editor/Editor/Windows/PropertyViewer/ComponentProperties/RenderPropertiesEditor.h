#pragma once

#include "MPE/Core/_CORE.h"
#include "Editor/Editor/Windows/PropertyViewer/ComponentProperties/IComponentPropertyEditor.h"
#include "Editor/Editor/ECS/Components/Graphical/RenderComponent.h"
#include "Editor/Editor/ECS/ECS.h"

#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Shaders/Shader.h"

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
class MPE_EDITOR_API RenderPropertiesEditor : public IComponentPropertyEditor
{
  public:
    RenderPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
    void Draw() override;
    bool IsModified() const override;
    void ApplyChanges() override;

  private:
    ECS::ECS& m_ECS;
    ECS::Entity m_entity;
    ECS::RenderComponent& m_renderComponent;
    REF<VertexArray> m_vertexArray;
    REF<Shader> m_shader;
    bool m_isModified = false;
};
// {
//   public:
//     static void DrawRenderPropertiesEditor(ECS::ECS& ecs, ECS::Entity entity);
// };
}