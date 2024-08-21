#include "TranslationSystem.h"

namespace MPE
{
namespace ECS
{
TranslationSystem::TranslationSystem() {};
TranslationSystem::~TranslationSystem() {};

void TranslationSystem::Update(ComponentManager& componentManager, float deltaTime)
{
    for (auto entity : m_entities)
    {
        auto& translation = componentManager.GetComponentArray<TransformComponent>()->GetData(entity);
        // auto& translation = componentManager.GetComponent<TransformComponent>(entity);
        // auto& velocity = componentManager.GetComponent<VelocityComponent>(entity);

        // translation.position += velocity.velocity * deltaTime;
        translation.position += deltaTime;
    }
}
}
}