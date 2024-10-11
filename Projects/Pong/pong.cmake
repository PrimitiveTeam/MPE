add_executable(PONG
  "${PROJECT_SOURCE_DIR}/Projects/Pong/ProjectSelector.cpp")

target_include_directories(PONG PRIVATE ${MPE_PUBLIC_INCLUDES})

file(GLOB_RECURSE PONG_CPP
  "${PROJECT_SOURCE_DIR}/Projects/Pong/*.cpp"
  "${PROJECT_SOURCE_DIR}/Projects/Pong/Core/*.cpp")

file(GLOB_RECURSE PONG_H
  "${PROJECT_SOURCE_DIR}/Projects/Pong/*.h"
  "${PROJECT_SOURCE_DIR}/Projects/Pong/Core/*.h")

add_library(PONG_SRC STATIC ${PONG_CPP})
target_include_directories(PONG_SRC PUBLIC
  ${PONG_H}
  ${MPE_PUBLIC_INCLUDES}
  ${MPE_EDITOR_PUBLIC_INCLUDES}
)

# COMPILER DEFINITIONS FOR PONG_SRC
target_compile_definitions(PONG_SRC PUBLIC ${MPE_PUBLIC_DEFINITIONS})

if(${VERBOSE})
  get_target_property(PONG_SRC_DEFINITIONS_LIST PONG_SRC COMPILE_DEFINITIONS)

  message("
-----------------------------------------------------------
PONG_SRC COMPILE DEFINITIONS:\n")

  foreach(DEFINITION ${PONG_SRC_DEFINITIONS_LIST})
    message(STATUS "${DEFINITION}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()

target_link_libraries(PONG_SRC PUBLIC MPE MPE_EDITOR)
target_link_libraries(PONG PUBLIC MPE MPE_EDITOR)
target_link_libraries(PONG PUBLIC PONG_SRC)

set_target_properties(PONG PROPERTIES OUTPUT_NAME "MPE-PONG")

# COMPILER DEFINITIONS FOR PONG
target_compile_definitions(PONG PUBLIC ${MPE_PUBLIC_DEFINITIONS})

if(${VERBOSE})
  get_target_property(PONG_DEFINITIONS_LIST PONG COMPILE_DEFINITIONS)

  message("
-----------------------------------------------------------
PONG COMPILE DEFINITIONS:\n")

  foreach(DEFINITION ${PONG_DEFINITIONS_LIST})
    message(STATUS "${DEFINITION}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()

# Copy the /Project/*/Data folder to the build directory
add_custom_command(
  TARGET PONG
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/Projects/Pong/Data
  $<TARGET_FILE_DIR:PONG>/Data
)

# Copy the /Project/*/Data folder to the install directory
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/Projects/Pong/Data
  DESTINATION bin
)

# INSTALLATION PROCEDURE
install(
  TARGETS PONG
  LIBRARY DESTINATION bin
  ARCHIVE DESTINATION bin
  RUNTIME DESTINATION bin)

install(FILES $<TARGET_RUNTIME_DLLS:PONG> DESTINATION bin)

if(${VERBOSE})
  message(STATUS "MPE-PONG ADDED.")
endif()

if(COMPILATION_PLATFORM STREQUAL "OSX" AND MPE_ANGLE)
    modify_dylib_paths(PONG)
endif(COMPILATION_PLATFORM STREQUAL "OSX" AND MPE_ANGLE)