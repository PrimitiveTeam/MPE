# INSTALLATION PROCEDURE FOR MPE
install(
  TARGETS MPE
  LIBRARY DESTINATION bin
  ARCHIVE DESTINATION bin
  RUNTIME DESTINATION bin)

# Copy the /MPE/Resources folder to Install/bin/Data
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/Resources/Shaders
  DESTINATION bin/Data
)

# Copy the /MPE/Resources folder to /bin/Data
add_custom_command(
  TARGET MPE
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/Resources
  $<TARGET_FILE_DIR:MPE>/Data
  COMMENT "Copying MPE Resources DLLs to MPE build..."
)

if(${INSTALL_DLLS})
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  # EXAMPLES FOR FUTURE
  # install(FILES ${GTK_DLL_DEBUG_FILES} DESTINATION bin) install(FILES
  # ${MPE_DLL_DEBUG_FILES} DESTINATION bin)
  # install(FILES ${BOOST_PYTHON_DLL_DEBUG_FILES} DESTINATION bin)
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    # EXAMPLES FOR FUTURE
    # install(FILES ${GTK_DLL_RELEASE_FILES} DESTINATION bin) install(FILES
    # ${MPE_DLL_RELEASE_FILES} DESTINATION bin)
    # install(FILES ${BOOST_PYTHON_DLL_RELEASE_FILES} DESTINATION bin)
  endif()
endif()

if(MPE_ANGLE)
  add_custom_command(
    TARGET MPE
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${ANGLE_DLLS}
    $<TARGET_FILE_DIR:MPE>
    COMMENT "Copying ANGLE DLLs to MPE build..."
  )

  # Also add install for dlls
  install(
    FILES ${ANGLE_DLLS}
    DESTINATION bin
  )
endif(MPE_ANGLE)