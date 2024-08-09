add_executable(FREETYPE_TEST "${PROJECT_SOURCE_DIR}/Projects/FreeType/main.cpp")

target_link_libraries(FREETYPE_TEST PRIVATE
  MPE
)

target_include_directories(FREETYPE_TEST PRIVATE
  ${MPE_PUBLIC_INCLUDES}
)

# COMPILER DEFINITIONS FOR FREETYPE_TEST
target_compile_definitions(FREETYPE_TEST PUBLIC ${MPE_PUBLIC_DEFINITIONS})

if(${VERBOSE})
  get_target_property(FREETYPE_TEST_DEFINITIONS_LIST FREETYPE_TEST COMPILE_DEFINITIONS)

  message("
-----------------------------------------------------------
FREETYPE_TEST COMPILE DEFINITIONS:\n")

  foreach(DEFINITION ${FREETYPE_TEST_DEFINITIONS_LIST})
    message(STATUS "${DEFINITION}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()

# Copy the /Project/*/Data folder to the build directory
add_custom_command(
  TARGET FREETYPE_TEST
  POST_BUILD    
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/Projects/FreeType/Data
  $<TARGET_FILE_DIR:FREETYPE_TEST>/Data
)

# Copy the /Project/*/Data folder to the install directory
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/Projects/FreeType/Data
  DESTINATION bin
)

# INSTALLATION PROCEDURE
install(
  TARGETS FREETYPE_TEST
  LIBRARY DESTINATION bin
  ARCHIVE DESTINATION bin
  RUNTIME DESTINATION bin)

install(FILES $<TARGET_RUNTIME_DLLS:FREETYPE_TEST> DESTINATION bin)