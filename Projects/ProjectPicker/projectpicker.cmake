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
file(GLOB_RECURSE TEST_LAYERS_CPP
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/*.cpp")
file(GLOB_RECURSE TEST_LAYERS_H
  "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/*.h")
add_library(TEST_LAYERS STATIC ${TEST_LAYERS_CPP})
target_include_directories(TEST_LAYERS PUBLIC
  ${TEST_LAYERS_H}
  ${MPE_PUBLIC_INCLUDES}
  ${MPE_EDITOR_PUBLIC_INCLUDES}
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