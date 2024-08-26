file(
    GLOB_RECURSE
    MPE_EDITOR_CPP

    # /Editor
    "${PROJECT_SOURCE_DIR}/Editor/Editor/Grid/Grid.cpp"

    "${PROJECT_SOURCE_DIR}/Editor/Editor/Dialog/SimpleDialog.cpp"

    # /Editor/ECS/Base
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ECS/ECS.cpp"

    # /Editor/ECS/Systems
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ECS/Systems/TransformSystem.cpp"

    # /Editor/ECS/Utility
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ECS/Utility/TagQuery.cpp"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ECS/Utility/RotationUtilities.cpp"

    # /Editor/Objects/Base
    "${PROJECT_SOURCE_DIR}/Editor/Editor/Objects/Object.cpp"

    # /Editor/Objects
    "${PROJECT_SOURCE_DIR}/Editor/Editor/Objects/Cube.cpp"

    # /Editor/Scene
    "${PROJECT_SOURCE_DIR}/Editor/Editor/Scene/Scene.cpp"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/Scene/SceneManager.cpp"

    # /Editor/ObjectHierarchy
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ObjectHierarchy/ObjectHierarchy.cpp"

    # /Editor/PropertyViewer
    "${PROJECT_SOURCE_DIR}/Editor/Editor/PropertyViewer/ComponentProperties/HierarchyPropertiesEditor.cpp"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/PropertyViewer/ComponentProperties/TagPropertiesEditor.cpp"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/PropertyViewer/ComponentProperties/TransformPropertiesEditor.cpp"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/PropertyViewer/PropertyViewer.cpp"
)

file(
    GLOB_RECURSE
    MPE_EDITOR_H

    # /
    "${PROJECT_SOURCE_DIR}/Editor/MPEECS.h"
    "${PROJECT_SOURCE_DIR}/Editor/MPEEDITOR.h"

    # /Editor
    "${PROJECT_SOURCE_DIR}/Editor/Editor/Grid/Grid.h"

    "${PROJECT_SOURCE_DIR}/Editor/Editor/Dialog/SimpleDialog.h"

    # /Editor/ECS
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ECS/ECS.h"

    # /Editor/ECS/Components
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ECS/Components/Core/TransformComponent.h"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ECS/Components/Core/TagComponent.h"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ECS/Components/Editor/HierarchyComponent.h"

    # /Editor/ECS/Systems
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ECS/Systems/TransformSystem.h"

    # /Editor/ECS/Utility
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ECS/Utility/RotationUtilities.h"

    # /Editor/Objects/Base
    "${PROJECT_SOURCE_DIR}/Editor/Editor/Objects/Object.h"

    # /Editor/Objects
    "${PROJECT_SOURCE_DIR}/Editor/Editor/Objects/Cube.h"

    # /Editor/Scene
    "${PROJECT_SOURCE_DIR}/Editor/Editor/Scene/Scene.h"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/Scene/SceneManager.h"

    # /Editor/ObjectHierarchy
    "${PROJECT_SOURCE_DIR}/Editor/Editor/ObjectHierarchy/ObjectHierarchy.h"

    # /Editor/PropertyViewer
    "${PROJECT_SOURCE_DIR}/Editor/Editor/PropertyViewer/ComponentProperties/IComponentPropertyEditor.h"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/PropertyViewer/ComponentProperties/TransformPropertiesEditor.h"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/PropertyViewer/ComponentProperties/TagPropertiesEditor.h"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/PropertyViewer/ComponentProperties/HierarchyPropertiesEditor.h"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/PropertyViewer/Properties.h"
    "${PROJECT_SOURCE_DIR}/Editor/Editor/PropertyViewer/PropertyViewer.h"
)

# PRINT MPE EDITOR SOURCE FILES
if(${VERBOSE})
    message("
MPE EDITOR SOURCE AND HEADER FILES

EDITOR SOURCE FILES:\n")

    foreach(MPE_EDITOR_CPP_FILE ${MPE_EDITOR_CPP})
        message("${MPE_EDITOR_CPP_FILE}")
    endforeach()

    message("
EDITOR HEADER FILES:\n")

    foreach(MPE_EDITOR_H_FILE ${MPE_EDITOR_H})
        message("${MPE_EDITOR_H_FILE}")
    endforeach()

    message("
-----------------------------------------------------------")
endif()