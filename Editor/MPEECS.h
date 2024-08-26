#pragma once

// Need this for euler/quaternion conversions
#define GLM_ENABLE_EXPERIMENTAL

// ----- ECS -----
// Base
#include "Editor/Editor/ECS/ECS.h"
// Components
#include "Editor/Editor/ECS/Components/Core/TagComponent.h"
#include "Editor/Editor/ECS/Components/Core/TransformComponent.h"
// Systems
#include "Editor/Editor/ECS/Systems/TransformSystem.h"
// Utilities
#include "Editor/Editor/ECS/Utility/RotationUtilities.h"
// ----- ECS -----