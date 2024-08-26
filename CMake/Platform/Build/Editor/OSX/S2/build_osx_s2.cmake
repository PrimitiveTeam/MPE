# NOT EQUAL TO UNIX
target_link_libraries(
  MPE_EDITOR
  PUBLIC MPE
  PUBLIC fmt::fmt
  PUBLIC spdlog::spdlog

  # OpenGL::GL
  PUBLIC glad
  PUBLIC glfw
  PUBLIC imgui
  PUBLIC glm::glm
  PUBLIC Stb

  # PUBLIC freetype
  PUBLIC ${FREETYPE_LIBRARIES}
  PUBLIC OpenAL::OpenAL
  PUBLIC EnTT::EnTT

  # CURRENTLY NOT IN USE: imguizmo::imguizmo yaml-cpp
)

target_link_libraries(
  MPE_EDITOR
  PUBLIC ${COCOA_LIBRARY}
)

if(MPE_ANGLE)
  target_include_directories(MPE_EDITOR
    PUBLIC ${angle_Include}
  )

  target_link_libraries(
    MPE_EDITOR
    PUBLIC ${ANGLE_GLESv2_LIBRARY}
    PUBLIC ${ANGLE_EGL_LIBRARY}
  )

  # Set RPATH for the MPE target
  # set_target_properties(MPE PROPERTIES
  # INSTALL_RPATH "@executable_path"
  # BUILD_WITH_INSTALL_RPATH TRUE
  # )
endif(MPE_ANGLE)

# find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
target_include_directories(
  MPE_EDITOR
  PUBLIC ${Stb_INCLUDE_DIRS}
  PUBLIC ${FREETYPE_INCLUDE_DIRS}
)

# ADD MPEPCH.H AS A PRECOMPILED HEADER FILE
target_precompile_headers(MPE_EDITOR PUBLIC
  "${PROJECT_SOURCE_DIR}/MPE/MPEPCH.h"
  "${PROJECT_SOURCE_DIR}/MPE/MPEPLAT.h"
  "${PROJECT_SOURCE_DIR}/MPE/Vendor/GLM/GLM.h"
)

# ADD INCLUDE DIRECTORIES TO MAKE INCLUDES EASY TO MANAGE
target_include_directories(MPE_EDITOR
  PRIVATE "${PROJECT_SOURCE_DIR}"
  PUBLIC "${PROJECT_SOURCE_DIR}/MPE"
  PUBLIC "${PROJECT_SOURCE_DIR}/Platform"
  PUBLIC "${PROJECT_SOURCE_DIR}/Editor"
)