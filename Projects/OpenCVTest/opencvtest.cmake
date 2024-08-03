# ##############################################################################
# ADDING OPENCV_TEST EXECUTABLE
if(${MPE_PROJECTS} AND ${MPE_PROJECT_OPENCVTEST})
  add_executable(OPENCV_TEST "${PROJECT_SOURCE_DIR}/Projects/OpenCVTest/OpenCVTest.cpp")

  target_link_libraries(OPENCV_TEST PRIVATE
    MPE
    ${OpenCV_LIBS}
  )

  target_include_directories(OPENCV_TEST PRIVATE
    ${MPE_PUBLIC_INCLUDES}
    ${OpenCV_LIBS}
  )

  # COMPILER DEFINITIONS FOR OPENCV_TEST
  target_compile_definitions(OPENCV_TEST PUBLIC ${MPE_PUBLIC_DEFINITIONS})

  if(${VERBOSE})
    get_target_property(OPENCV_TEST_DEFINITIONS_LIST OPENCV_TEST COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
OPENCV_TEST COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${OPENCV_TEST_DEFINITIONS_LIST})
      message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

  # Copy the /Project/*/Data folder to the build directory
  add_custom_command(
    TARGET OPENCV_TEST
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Projects/OpenCVTest/Data
    $<TARGET_FILE_DIR:OPENCV_TEST>/Data
  )

  # Copy the /Project/*/Data folder to the install directory
  install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/Projects/OpenCVTest/Data
    DESTINATION bin
  )

  # INSTALLATION PROCEDURE
  install(
    TARGETS OPENCV_TEST
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin)

  install(FILES $<TARGET_RUNTIME_DLLS:OPENCV_TEST> DESTINATION bin)
endif(${MPE_PROJECTS} AND ${MPE_PROJECT_OPENCVTEST})