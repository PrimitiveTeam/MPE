
target_link_libraries(
  MPE
  PUBLIC fmt::fmt
  PUBLIC spdlog::spdlog

  # OpenGL::GL
  PUBLIC glad
  PUBLIC glfw
  PUBLIC imgui
  PUBLIC glm::glm
  PUBLIC Stb
  PUBLIC freetype
  # PUBLIC freetype-gl
  PUBLIC OpenAL::OpenAL
  PUBLIC EnTT::EnTT

  # CURRENTLY NOT IN USE: imguizmo::imguizmo yaml-cpp
)

target_link_libraries(
  MPE
  PUBLIC ${OpenCV_LIBS}
)

if(MPE_ANGLE)
  target_include_directories(MPE
    PUBLIC ${angle_Include}
  )

  target_link_libraries(
    MPE
    PUBLIC ${ANGLE_GLESv2_LIBRARY}
    PUBLIC ${ANGLE_EGL_LIBRARY}
  )

  # message(FATAL_ERROR "ANGLE LIBS: ${ANGLE_GLESv2_LIBRARY} ${ANGLE_EGL_LIBRARY}")
endif(MPE_ANGLE)

# find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
target_include_directories(MPE
  PUBLIC
  ${Stb_INCLUDE_DIRS}
)

target_include_directories(MPE
  PUBLIC
  ${OpenCV_INCLUDE_DIRS}
)

# ADD MPEPCH.H AS A PRECOMPILED HEADER FILE
target_precompile_headers(MPE PUBLIC
  "${PROJECT_SOURCE_DIR}/MPE/MPEPCH.h")

# ADD INCLUDE DIRECTORIES TO MAKE INCLUDES EASY TO MANAGE
target_include_directories(MPE
  PRIVATE "${PROJECT_SOURCE_DIR}"
  PUBLIC "${PROJECT_SOURCE_DIR}/MPE"
)

# INSTALLATION FOR LIBRARIES
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  # MPE DEBUG DLLS
  set(MPE_DLL_FILES
    ${PROJECT_SOURCE_DIR}/Build/Debug/MPE.dll)
  set(DEPENENDENCY_DLL_FILES
    ${PROJECT_SOURCE_DIR}/Build/Debug/fmtd.dll
    ${PROJECT_SOURCE_DIR}/Build/Debug/spdlogd.dll

    # ${PROJECT_SOURCE_DIR}/Build/Debug/gladd.dll
    # ${PROJECT_SOURCE_DIR}/Build/Debug/glfw3d.dll
    # ${PROJECT_SOURCE_DIR}/Build/Debug/imguid.dll
    # ${PROJECT_SOURCE_DIR}/Build/Debug/glmd.dll
  )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  # MPE RELEASE DLLS
  set(MPE_DLL_FILES
    ${PROJECT_SOURCE_DIR}/Build/Release/MPE.dll)
  set(DEPENENDENCY_DLL_FILES
    ${PROJECT_SOURCE_DIR}/Build/Release/fmt.dll
    ${PROJECT_SOURCE_DIR}/Build/Release/spdlog.dll

    # ${PROJECT_SOURCE_DIR}/Build/Release/glad.dll
    # ${PROJECT_SOURCE_DIR}/Build/Release/glfw3.dll
    # ${PROJECT_SOURCE_DIR}/Build/Release/imgui.dll
    # ${PROJECT_SOURCE_DIR}/Build/Release/glm.dll
  )
endif()

if(${VERBOSE})
  message("
-----------------------------------------------------------
MPE DLL FILES:\n")

  foreach(MPE_DLL ${MPE_DLL_FILES})
    message(STATUS "${MPE_DLL}")
  endforeach()

  message("
DEPENDENCY DLL FILES:\n")

  foreach(MPE_DEPENENDENCY_DLL ${DEPENENDENCY_DLL_FILES})
    message(STATUS "${MPE_DEPENENDENCY_DLL}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()