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

  # CURRENTLY NOT IN USE: imguizmo::imguizmo yaml-cpp
)

# find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
target_include_directories(MPE
  PUBLIC
  ${Stb_INCLUDE_DIRS}
)

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