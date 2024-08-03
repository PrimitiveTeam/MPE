set(USE_VCPKG OFF)

if(${VERBOSE})
    message(STATUS "VCPKG STATUS: ${USE_VCPKG}")
endif()

# Set pkg-config environment variables
set(ENV{PKG_CONFIG_SYSROOT_DIR} "${CMAKE_SYSROOT}")
message(STATUS "PKG_CONFIG_SYSROOT_DIR: $ENV{PKG_CONFIG_SYSROOT_DIR}")
set(ENV{PKG_CONFIG_PATH} "${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/pkgconfig")
message(STATUS "PKG_CONFIG_PATH: $ENV{PKG_CONFIG_PATH}")

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

find_package(PkgConfig REQUIRED)

# OPENGL
pkg_check_modules(OPENGL REQUIRED opengl)

if(OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_directories(${OPENGL_LIBRARY_DIRS})
    add_definitions(${OPENGL_CFLAGS_OTHER})
    message(STATUS "Found opengl: ${OPENGL_LIBRARIES}")
    message(STATUS "OpenGL include directories: ${OPENGL_INCLUDE_DIRS}")
    message(STATUS "OpenGL library directories: ${OPENGL_LIBRARY_DIRS}")
else()
    message(FATAL_ERROR "opengl library not found")
endif()

# GLFW
pkg_check_modules(GLFW3 REQUIRED glfw3)

if(GLFW3_FOUND)
    # set(GLFW3_INCLUDE_DIRS "/usr/include/GLFW")

    # set(GLFW3_LIBRARIES "/usr/lib/x86_64-linux-gnu/libglfw.so")
    include_directories(${GLFW3_INCLUDE_DIRS})
    link_directories(${GLFW3_LIBRARY_DIRS})
    add_definitions(${GLFW3_CFLAGS_OTHER})
    message(STATUS "Found glfw3: ${GLFW3_LIBRARIES}")
    message(STATUS "GLFW3 include directories: ${GLFW3_INCLUDE_DIRS}")
    message(STATUS "GLFW3 library directories: ${GLFW3_LIBRARY_DIRS}")
else()
    message(FATAL_ERROR "glfw3 library not found")
endif()

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
target_include_directories(imgui
    PUBLIC "${imgui_DIR}"
    PRIVATE ${GLFW3_INCLUDE_DIRS}
)
target_link_libraries(imgui PRIVATE ${GLFW3_LIBRARIES})

# GTK#
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# STB
set(Stb_DIR ${UNIVERSAL_VENDOR_DIR}/stb)
add_library(Stb INTERFACE
    "${Stb_DIR}"
)
target_include_directories(Stb INTERFACE
    "${Stb_DIR}"
)

if(GTK3_FOUND)
    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})
    add_definitions(${GTK3_CFLAGS_OTHER})
    message(STATUS "Found gtk3: ${GTK3_LIBRARIES}")
    message(STATUS "GTK3 include directories: ${GTK3_INCLUDE_DIRS}")
    message(STATUS "GTK3 library directories: ${GTK3_LIBRARY_DIRS}")
else()
    message(FATAL_ERROR "gtk3 library not found")
endif()

# fmt
# pkg_check_modules(FMT REQUIRED fmt)

# if(FMT_FOUND)
# set(FMT_LIBRARY_DIRS "/opt/rpi-sysroot/usr/lib/aarch64-linux-gnu")

# # set(GLFW3_LIBRARIES "/usr/lib/x86_64-linux-gnu/libglfw.so")
# include_directories(${FMT_INCLUDE_DIRS})
# link_directories(${FMT_LIBRARY_DIRS})
# add_definitions(${FMT_CFLAGS_OTHER})
# message(STATUS "Found fmt: ${FMT_LIBRARIES}")
# message(STATUS "fmt include directories: ${FMT_INCLUDE_DIRS}")
# message(STATUS "fmt library directories: ${FMT_LIBRARY_DIRS}")
# else()
# message(FATAL_ERROR "fmt library not found")
# endif()

# spdlog
# pkg_check_modules(SPDLOG REQUIRED spdlog)

# if(SPDLOG_FOUND)
# # set(SPDLOG_LIBRARY_DIRS "/opt/rpi-sysroot/usr/local/lib")
# # set(SPDLOG_INCLUDE_DIRS "/opt/rpi-sysroot/usr/local/include")

# include_directories(${SPDLOG_INCLUDE_DIRS})
# link_directories(${SPDLOG_LIBRARY_DIRS})
# add_definitions(${SPDLOG_CFLAGS_OTHER})
# message(STATUS "Found spdlog: ${SPDLOG_LIBRARIES}")
# message(STATUS "spdlog include directories: ${SPDLOG_INCLUDE_DIRS}")
# message(STATUS "spdlog library directories: ${SPDLOG_LIBRARY_DIRS}")
# else()
# message(FATAL_ERROR "spdlog library not found")
# endif()
set(spdlog_DIR ${VENDOR_DIR}/spdlog)

file(GLOB_RECURSE SPDLOG_S
    "${spdlog_DIR}/src/spdlog.cpp"
    "${spdlog_DIR}/src/bundled_fmtlib_format.cpp"
    "${spdlog_DIR}/src/async.cpp"
    "${spdlog_DIR}/src/cfg.cpp"
    "${spdlog_DIR}/src/color_sinks.cpp"
    "${spdlog_DIR}/src/file_sinks.cpp"
    "${spdlog_DIR}/src/stdout_sinks.cpp"
)

add_definitions(-DSPDLOG_COMPILED_LIB)

add_library(spdlog STATIC
    ${SPDLOG_S}
)
target_include_directories(spdlog
    PUBLIC "${spdlog_DIR}/include"
)

message(STATUS "spdlog_DIR: ${spdlog_DIR}")
message(STATUS "SPDLOG_S: ${SPDLOG_S}")
message(STATUS "spdlog include directories: ${spdlog_DIR}/include")

# pkg_check_modules(GLM REQUIRED glm)

# if(GLM_FOUND)
# include_directories(${GLM_INCLUDE_DIRS})
# link_directories(${GLM_LIBRARY_DIRS})
# add_definitions(${GLM_CFLAGS_OTHER})
# message(STATUS "Found glm: ${GLM_LIBRARIES}")
# else()
# message(FATAL_ERROR "glm library not found")
# endif()
if(${VERBOSE})
    message(STATUS "glad_DIR: ${glad_DIR}")
    message(STATUS "imgui_DIR: ${imgui_DIR}")
    message(STATUS "GTK3_INCLUDE_DIRS: ${GTK3_INCLUDE_DIRS}")

    # message(STATUS "glfw3_DIR: ${glfw3_DIR}")
    # message(STATUS "glm_DIR: ${glm_DIR}")
    # message(STATUS "GTest_DIR: ${GTest_DIR}")
    message(STATUS "CUSTOM LIBRARY PATHS SET.")
endif()
