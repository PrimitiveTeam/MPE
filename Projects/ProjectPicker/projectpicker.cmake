# ADD "ProjectPicker" EXECUTABLE - THE ENTRYPOINT TO MPE
add_executable(ProjectPicker "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/ProjectPicker.cpp")

target_link_libraries(ProjectPicker PRIVATE
  MPE
  MPE_EDITOR
)
target_include_directories(
  ProjectPicker
  PRIVATE ${MPE_PUBLIC_INCLUDES}
  PRIVATE ${MPE_EDITOR_PUBLIC_INCLUDES}
)

# COMPILER DEFINITIONS FOR ProjectPicker
target_compile_definitions(ProjectPicker PUBLIC ${MPE_PUBLIC_DEFINITIONS})

if(${VERBOSE})
  get_target_property(ProjectPicker_DEFINITIONS_LIST ProjectPicker COMPILE_DEFINITIONS)

  message("
-----------------------------------------------------------
ProjectPicker COMPILE DEFINITIONS:\n")

  foreach(DEFINITION ${ProjectPicker_DEFINITIONS_LIST})
    message(STATUS "${DEFINITION}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()

# ADDING TEST LAYERS
set(TEST_LAYERS_CPP
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/ClearColorTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/ColorAnimationTriangleTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/ColorTriangleTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/CubeAbstractionTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/GeneralTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/GridTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/MultiCubeTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/NativeTextTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/ObjectHierarchyTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/PropertyViewerTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/RectangleTransformationTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SceneTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleAudioTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleCubeTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleEcsTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleLightingTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimplePerspectiveCameraTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleRectangleTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleTriangleTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/TextureRectangleTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/TexturesTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/TriangleTransformationTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SphereTest.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/PBRTest.cpp"
)
set(TEST_LAYERS_H
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/ClearColorTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/ColorAnimationTriangleTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/ColorTriangleTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/CubeAbstractionTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/GeneralTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/GridTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/MultiCubeTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/NativeTextTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/ObjectHierarchyTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/PropertyViewerTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/RectangleTransformationTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SceneTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleAudioTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleCubeTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleEcsTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleLightingTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimplePerspectiveCameraTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleRectangleTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SimpleTriangleTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/TextureRectangleTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/TexturesTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/TriangleTransformationTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/SphereTest.h"
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/PBRTest.h"
)
add_library(TEST_LAYERS STATIC ${TEST_LAYERS_CPP})
target_include_directories(TEST_LAYERS PUBLIC
  ${MPE_PUBLIC_INCLUDES}
  ${MPE_EDITOR_PUBLIC_INCLUDES}
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests"
)

target_link_libraries(TEST_LAYERS PUBLIC
  MPE
  MPE_EDITOR
)

# COMPILER DEFINITIONS FOR TEST_LAYERS
target_compile_definitions(TEST_LAYERS PUBLIC ${MPE_PUBLIC_DEFINITIONS})

if(${VERBOSE})
  get_target_property(TEST_LAYERS_DEFINITIONS_LIST TEST_LAYERS COMPILE_DEFINITIONS)

  message("
-----------------------------------------------------------
TEST_LAYERS COMPILE DEFINITIONS:\n")

  foreach(DEFINITION ${TEST_LAYERS_DEFINITIONS_LIST})
    message(STATUS "${DEFINITION}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()

target_link_libraries(ProjectPicker PUBLIC TEST_LAYERS)

# target_compile_features(SANDBOX PUBLIC ${CXX_VERSION_NAME})
set_target_properties(ProjectPicker PROPERTIES VERSION ${PROJECT_FULL_VERSION})
set_target_properties(ProjectPicker PROPERTIES OUTPUT_NAME "MPE-ProjectPicker")

# Copy the /Project/*/Data folder to the build directory
add_custom_command(
  TARGET ProjectPicker
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Data
  $<TARGET_FILE_DIR:ProjectPicker>/Data
)

# Copy the /Project/*/Data folder to the install directory
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Data
  DESTINATION bin
)

# INSTALLATION PROCEDURE
install(
  TARGETS ProjectPicker
  LIBRARY DESTINATION bin
  ARCHIVE DESTINATION bin
  RUNTIME DESTINATION bin)

install(FILES $<TARGET_RUNTIME_DLLS:ProjectPicker> DESTINATION bin)

if(COMPILATION_PLATFORM STREQUAL "OSX")
  if(MPE_ANGLE)
    modify_dylib_paths(ProjectPicker)
  endif()
endif()

if(${VERBOSE})
  message(STATUS "MPE-ProjectPicker ADDED.")
endif()