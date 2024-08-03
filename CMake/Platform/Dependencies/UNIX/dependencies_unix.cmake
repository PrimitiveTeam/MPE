set(USE_VCPKG OFF)

if(${VERBOSE})
    message(STATUS "VCPKG STATUS: ${USE_VCPKG}")
endif()

# message(STATUS "VCPKG NOT SUPPORTED ON UNIX SYSTEMS.")
if(${VERBOSE})
    message(STATUS "ADDING CUSTOM PATHS FOR SPECIFIC LIBRARIES...")
endif()

# GLAD
set(glad_DIR "${UNIVERSAL_VENDOR_DIR}/glad")
add_library(glad STATIC "${glad_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${glad_DIR}/include")

# Ensure that glad is compiled with -fPIC
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)

# IMGUI
set(imgui_DIR ${UNIVERSAL_VENDOR_DIR}/imgui)

file(GLOB_RECURSE IMGUI_S
    "${imgui_DIR}/imgui.cpp"
    "${imgui_DIR}/imgui_draw.cpp"
    "${imgui_DIR}/imgui_tables.cpp"
    "${imgui_DIR}/imgui_widgets.cpp"
    "${imgui_DIR}/imgui_demo.cpp"
)

list(APPEND IMGUI_S
    "${imgui_DIR}/backends/imgui_impl_glfw.cpp"
    "${imgui_DIR}/backends/imgui_impl_opengl3.cpp"
)

add_library(imgui STATIC
    ${IMGUI_S}
)
target_include_directories(imgui PUBLIC
    "${imgui_DIR}"
    ${glfw3_INCLUDE_DIRS}
)
target_link_libraries(imgui PRIVATE glfw)

# GTK#
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# STB
set(Stb_DIR ${UNIVERSAL_VENDOR_DIR}/stb)
add_library(Stb INTERFACE
    "${Stb_DIR}"
)
target_include_directories(Stb INTERFACE
    "${Stb_DIR}"
)

if(${VERBOSE})
    message(STATUS "glad_DIR: ${glad_DIR}")
    message(STATUS "imgui_DIR: ${imgui_DIR}")
    message(STATUS "GTK3_INCLUDE_DIRS: ${GTK3_INCLUDE_DIRS}")

    # message(STATUS "glfw3_DIR: ${glfw3_DIR}")
    # message(STATUS "glm_DIR: ${glm_DIR}")
    # message(STATUS "GTest_DIR: ${GTest_DIR}")
    message(STATUS "CUSTOM LIBRARY PATHS SET.")
endif()