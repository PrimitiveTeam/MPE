target_link_libraries(
  MPE
  PUBLIC ${FMT_LIBRARIES}
  PUBLIC spdlog
  PUBLIC ${OPENGL_LIBRARIES}
  PUBLIC glad
  PUBLIC ${GLFW3_LIBRARIES}
  PUBLIC imgui
  PUBLIC ${GLM_LIBRARIES}
  PUBLIC Stb
  PUBLIC ${GTK3_LIBRARIES}
  PUBLIC EnTT::EnTT

  # CURRENTLY NOT IN USE: imguizmo::imguizmo yaml-cpp
)

# find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
target_include_directories(MPE
  PUBLIC
  ${Stb_INCLUDE_DIRS}
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
endif(MPE_ANGLE)

if(MPE_USE_X11)
  target_link_libraries(MPE
    PUBLIC ${X11_LIBRARIES}
  )
endif()

if(MPE_USE_WAYLAND)
  message(FATAL_ERROR "NOT SETUP")
  target_link_libraries(MPE
    PUBLIC ${WAYLAND_CLIENT_LIBRARIES}
    PUBLIC ${WAYLAND_EGL_LIBRARIES}
  )
endif()

# ADD MPEPCH.H AS A PRECOMPILED HEADER FILE
target_precompile_headers(MPE PUBLIC
  "${PROJECT_SOURCE_DIR}/MPE/MPEPCH.h")

# ADD INCLUDE DIRECTORIES TO MAKE INCLUDES EASY TO MANAGE
target_include_directories(MPE
  PRIVATE "${PROJECT_SOURCE_DIR}"
  PUBLIC "${PROJECT_SOURCE_DIR}/MPE"
)

target_include_directories(MPE
  PUBLIC "${GTK3_INCLUDE_DIRS}")

if(MPE_USE_X11)
  target_include_directories(MPE
    PUBLIC ${X11_INCLUDE_DIR})
endif()

if(MPE_USE_WAYLAND)
  message(FATAL_ERROR "NOT SETUP")
  target_include_directories(MPE
    PUBLIC ${WAYLAND_CLIENT_INCLUDE_DIR}
    PUBLIC ${WAYLAND_EGL_INCLUDE_DIR})
endif()