#pragma once

// Need this for euler/quaternion conversions
#define GLM_ENABLE_EXPERIMENTAL

// ----- ECS -----
// Base
#include "MPE/Editor/ECS/ECS.h"
// Components
#include "MPE/Editor/ECS/Components/Core/TagComponent.h"
#include "MPE/Editor/ECS/Components/Core/TransformComponent.h"
// Systems
#include "MPE/Editor/ECS/Systems/TransformSystem.h"
// Utilities
#include "MPE/Editor/ECS/Utility/RotationUtilities.h"
// ----- ECS -----