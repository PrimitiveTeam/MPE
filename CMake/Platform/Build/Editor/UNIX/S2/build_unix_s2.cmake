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
  PUBLIC Freetype::Freetype
  PUBLIC OpenAL::OpenAL
  PUBLIC EnTT::EnTT

  # CURRENTLY NOT IN USE: imguizmo::imguizmo yaml-cpp
)

# find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
target_include_directories(MPE
  PUBLIC_EDITOR
  ${Stb_INCLUDE_DIRS}
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
endif(MPE_ANGLE)

if(MPE_USE_X11)
  target_link_libraries(MPE_EDITOR
    PUBLIC ${X11_LIBRARIES}
  )
endif()

if(MPE_USE_WAYLAND)
  message(FATAL_ERROR "NOT SETUP")
  target_link_libraries(MPE_EDITOR
    PUBLIC ${WAYLAND_CLIENT_LIBRARIES}
    PUBLIC ${WAYLAND_EGL_LIBRARIES}
  )
endif()

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

target_include_directories(MPE_EDITOR
  PUBLIC "${GTK3_INCLUDE_DIRS}")

if(MPE_USE_X11)
  target_include_directories(MPE_EDITOR
    PUBLIC ${X11_INCLUDE_DIR})
endif()

if(MPE_USE_WAYLAND)
  message(FATAL_ERROR "NOT SETUP")
  target_include_directories(MPE_EDITOR
    PUBLIC ${WAYLAND_CLIENT_INCLUDE_DIR}
    PUBLIC ${WAYLAND_EGL_INCLUDE_DIR})
endif()