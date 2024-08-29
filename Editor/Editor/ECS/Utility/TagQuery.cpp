#include "Editor/Editor/ECS/ECS.h"
#include "Editor/Editor/ECS/Components/Core/TagComponent.h"

namespace MPE
{
namespace ECS
{
std::vector<Entity> ECS::FindEntityByName(const std::string& name)
{
    std::vector<Entity> entities;
    auto view = m_registry.view<TagComponent>();

    for (auto entity : view)
    {
        const auto& tagComponent = view.get<TagComponent>(entity);
        if (tagComponent.name == name)
        {
            entities.push_back(entity);
        }
    }

    return entities;
}

std::vector<Entity> ECS::FindEntityByTag(const std::string& tag)
{
    std::vector<Entity> entities;
    auto view = m_registry.view<TagComponent>();

    for (auto entity : view)
    {
        const auto& tagComponent = view.get<TagComponent>(entity);
        if (tagComponent.tag == tag)
        {
            entities.push_back(entity);
        }
    }

    return entities;
}

std::vector<Entity> ECS::FindEntityByNameAndTag(const std::string& name, const std::string& tag)
{
    std::vector<Entity> entities;
    auto view = m_registry.view<TagComponent>();

    for (auto entity : view)
    {
        const auto& tagComponent = view.get<TagComponent>(entity);
        if (tagComponent.name == name && tagComponent.tag == tag)
        {
            entities.push_back(entity);
        }
    }

    return entities;
}
}
}