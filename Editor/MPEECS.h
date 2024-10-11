#pragma once

// ----- ECS -----
// Base
#include "Editor/Editor/ECS/ECS.h"
// Components
#include "Editor/Editor/ECS/Components/Core/TagComponent.h"
#include "Editor/Editor/ECS/Components/Core/TransformComponent.h"
#include "Editor/Editor/ECS/Components/Graphical/MaterialComponent.h"
#include "Editor/Editor/ECS/Components/Graphical/RenderComponent.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshComponent.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshFactory.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshRegenerator.h"
#include "Editor/Editor/ECS/Components/Meshes/Metadata/MeshMetadata.h"
#include "Editor/Editor/ECS/Components/Meshes/Metadata/SphereMetadataComponent.h"
// Systems
#include "Editor/Editor/ECS/Systems/TransformSystem.h"
#include "Editor/Editor/ECS/Systems/RenderSystem.h"
// Utilities
#include "Editor/Editor/ECS/Utility/RotationUtilities.h"
// ----- ECS -----