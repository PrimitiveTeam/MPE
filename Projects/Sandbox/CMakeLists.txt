# ##############################################################################
# PROJECTS SANDBOX
if(${MPE_PROJECTS} AND ${MPE_PROJECT_SANDBOX})
  # ADD "SANDBOX" EXECUTABLE - THE ENTRYPOINT TO MPE
  add_executable(SANDBOX "${PROJECT_SOURCE_DIR}/Projects/Sandbox/Sandbox.cpp")

  target_link_libraries(SANDBOX PRIVATE
    MPE
  )
  target_include_directories(SANDBOX PRIVATE ${MPE_PUBLIC_INCLUDES})

  # COMPILER DEFINITIONS FOR SANDBOX
  target_compile_definitions(SANDBOX PUBLIC ${MPE_PUBLIC_DEFINITIONS})

  if(${VERBOSE})
    get_target_property(SANDBOX_DEFINITIONS_LIST SANDBOX COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
SANDBOX COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${SANDBOX_DEFINITIONS_LIST})
      message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

  # ADDING SANDBOX 2D LAYER
  file(GLOB_RECURSE SANDBOX2D_CPP
    "${PROJECT_SOURCE_DIR}/Projects/Sandbox/Sandbox2D/*.cpp")
  file(GLOB_RECURSE SANDBOX2D_H
    "${PROJECT_SOURCE_DIR}/Projects/Sandbox/Sandbox2D/*.h")
  add_library(SANDBOX2D STATIC ${SANDBOX2D_CPP})
  target_include_directories(SANDBOX2D PUBLIC
    ${SANDBOX2D_H}
    ${MPE_PUBLIC_INCLUDES}
  )

  target_link_libraries(SANDBOX2D PUBLIC MPE)

  # COMPILER DEFINITIONS FOR SANDBOX2D
  target_compile_definitions(SANDBOX2D PUBLIC ${MPE_PUBLIC_DEFINITIONS})

  if(${VERBOSE})
    get_target_property(SANDBOX2D_DEFINITIONS_LIST SANDBOX2D COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
SANDBOX2D COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${SANDBOX2D_DEFINITIONS_LIST})
      message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

  target_link_libraries(SANDBOX PUBLIC SANDBOX2D)

  # target_compile_features(SANDBOX PUBLIC ${CXX_VERSION_NAME})
  set_target_properties(SANDBOX PROPERTIES VERSION ${PROJECT_FULL_VERSION})
  set_target_properties(SANDBOX PROPERTIES OUTPUT_NAME "MPE-SANDBOX")

  # Copy the /Project/*/Data folder to the build directory
  add_custom_command(
    TARGET SANDBOX
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Projects/Sandbox/Data
    $<TARGET_FILE_DIR:SANDBOX>/Data
  )

  # Copy the /Project/*/Data folder to the install directory
  install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/Projects/Sandbox/Data
    DESTINATION bin
  )

  # INSTALLATION PROCEDURE
  install(
    TARGETS SANDBOX
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin)

  install(FILES $<TARGET_RUNTIME_DLLS:SANDBOX> DESTINATION bin)

  if(${VERBOSE})
    message(STATUS "MPE-SANDBOX ADDED.")
  endif()
endif(${MPE_PROJECTS} AND ${MPE_PROJECT_SANDBOX})