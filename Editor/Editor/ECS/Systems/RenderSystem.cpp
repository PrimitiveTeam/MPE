#include "RenderSystem.h"

#include "Editor/Editor/ECS/ECS.h"
#include "Editor/Editor/ECS/Components/Core/TransformComponent.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshComponent.h"
#include "Editor/Editor/ECS/Components/Graphical/MaterialComponent.h"
#include "Editor/Editor/ECS/Components/Graphical/RenderComponent.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshRegenerator.h"
#include "Editor/Editor/Objects/Cameras/Camera.h"

#include "MPE/Renderer/Renderer.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
namespace ECS
{
void RenderSystem::operator()(entt::registry& registry, Camera& camera) const
{
    auto view = registry.view<TransformComponent, RenderComponent, MeshComponent, MaterialComponent>();

    for (auto entity : view)
    {
        auto& transform = view.get<TransformComponent>(entity);
        auto& renderComp = view.get<RenderComponent>(entity);
        auto& material = view.get<MaterialComponent>(entity);
        auto& mesh = view.get<MeshComponent>(entity);

        if (registry.all_of<SphereMetadataComponent>(entity))
        {
            auto& metadata = registry.get<SphereMetadataComponent>(entity);
            MPE::ECS::RegenerateMeshIfDirty(mesh, metadata, renderComp);
        }
        if (registry.all_of<GridMetadataComponent>(entity))
        {
            auto& metadata = registry.get<GridMetadataComponent>(entity);
            MPE::ECS::RegenerateMeshIfDirty(mesh, metadata, renderComp);
        }

        glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), transform.position);
        transformMatrix *= glm::toMat4(transform.rotation);
        transformMatrix = glm::scale(transformMatrix, transform.scale);

        renderComp.shader->Bind();
        renderComp.vertexArray->Bind();

        // MODELMAT and UNI_VPM is set in Renderer::Draw calls

        if (material.texture)
            material.texture->Bind();
        else
        // TODO: Find a better way to handle this
        {
#ifdef MPE_OPENGL
            std::dynamic_pointer_cast<MPE::OpenGLShader>(renderComp.shader)->InjectUniformFloat4("UNI_COLOR", material.color);
#elif MPE_OPENGLES
            std::dynamic_pointer_cast<MPE::OpenGLESShader>(renderComp.shader)->InjectUniformFloat4("UNI_COLOR", material.color);
#endif
        }

        Renderer::BeginScene(camera.GetProjection());
        if (mesh.lineDrawing)
        {
            if (mesh.indicesLines.size() > 0)
                Renderer::SubmitLines(renderComp.shader, renderComp.vertexArray, transformMatrix);
            else
                MPE_ASSERT(false, "Line drawing requested but no lines to draw.");
        }
        else
            Renderer::Submit(renderComp.shader, renderComp.vertexArray, transformMatrix);
        Renderer::EndScene();
    }
}
}
}