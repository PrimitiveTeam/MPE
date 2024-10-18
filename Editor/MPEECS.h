#pragma once

// ----- ECS -----
// Base
#include "Editor/Editor/ECS/ECS.h"
// Components
// Components/Core
#include "Editor/Editor/ECS/Components/Core/TagComponent.h"
#include "Editor/Editor/ECS/Components/Core/TransformComponent.h"
// Components/Cameras
#include "Editor/Editor/ECS/Components/Cameras/CameraComponent.h"
#include "Editor/Editor/ECS/Components/Cameras/OrthographicCameraComponent.h"
#include "Editor/Editor/ECS/Components/Cameras/PerspectiveCameraComponent.h"
// Components/Cameras/Controller
#include "Editor/Editor/ECS/Components/Cameras/Controller/CameraControllerComponent.h"
#include "Editor/Editor/ECS/Components/Cameras/Controller/OrthographicCameraControllerComponent.h"
// Components/Graphical
#include "Editor/Editor/ECS/Components/Graphical/MaterialComponent.h"
#include "Editor/Editor/ECS/Components/Graphical/RenderComponent.h"
// Components/Meshes
#include "Editor/Editor/ECS/Components/Meshes/MeshComponent.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshFactory.h"
#include "Editor/Editor/ECS/Components/Meshes/MeshRegenerator.h"
// Components/Meshes/Metadata
#include "Editor/Editor/ECS/Components/Meshes/Metadata/MeshMetadata.h"
#include "Editor/Editor/ECS/Components/Meshes/Metadata/SphereMetadataComponent.h"
// Systems
#include "Editor/Editor/ECS/Systems/TransformSystem.h"
#include "Editor/Editor/ECS/Systems/RenderSystem.h"
// Utilities
#include "Editor/Editor/ECS/Utility/RotationUtilities.h"
// ----- ECS -----