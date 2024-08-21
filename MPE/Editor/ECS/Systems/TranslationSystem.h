#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Editor/ECS/ECS.h"
#include "MPE/Editor/ECS/Systems/System.h"
#include "MPE/Editor/ECS/Base/ComponentManager.h"

// Components
#include "MPE/Editor/ECS/Components/TransformComponent.h"

namespace MPE
{
namespace ECS
{
class MPE_API TranslationSystem : public System
{
  public:
    TranslationSystem();
    ~TranslationSystem();

    void Update(ComponentManager& componentManager, float deltaTime);
};
}
}