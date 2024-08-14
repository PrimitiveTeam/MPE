if(COMPILATION_PLATFORM STREQUAL "WIN32")
  add_executable(OPENAL_TEST "${PROJECT_SOURCE_DIR}/Projects/OpenAl/main.cpp")
elseif(COMPILATION_PLATFORM STREQUAL "OSX")
  # add_executable(OPENAL_TEST "${PROJECT_SOURCE_DIR}/Projects/FreeType/main_osx.cpp")
endif()

target_link_libraries(OPENAL_TEST PRIVATE
  MPE
)

target_include_directories(OPENAL_TEST PRIVATE
  ${MPE_PUBLIC_INCLUDES}
)

# COMPILER DEFINITIONS FOR OPENAL_TEST
target_compile_definitions(OPENAL_TEST PUBLIC ${MPE_PUBLIC_DEFINITIONS})

if(${VERBOSE})
  get_target_property(OPENAL_TEST_DEFINITIONS_LIST OPENAL_TEST COMPILE_DEFINITIONS)

  message("
-----------------------------------------------------------
OPENAL_TEST COMPILE DEFINITIONS:\n")

  foreach(DEFINITION ${OPENAL_TEST_DEFINITIONS_LIST})
    message(STATUS "${DEFINITION}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()

# Copy the /Project/*/Data folder to the build directory
add_custom_command(
  TARGET OPENAL_TEST
  POST_BUILD    
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/Projects/OpenAL/Data
  $<TARGET_FILE_DIR:OPENAL_TEST>/Data
)

# Copy the /Project/*/Data folder to the install directory
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/Projects/OpenAL/Data
  DESTINATION bin
)

# INSTALLATION PROCEDURE
install(
  TARGETS OPENAL_TEST
  LIBRARY DESTINATION bin
  ARCHIVE DESTINATION bin
  RUNTIME DESTINATION bin)

install(FILES $<TARGET_RUNTIME_DLLS:OPENAL_TEST> DESTINATION bin)