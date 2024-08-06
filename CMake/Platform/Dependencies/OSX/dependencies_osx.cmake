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
    message(STATUS "Stb_DIR: ${Stb_DIR}")

    # message(STATUS "glfw3_DIR: ${glfw3_DIR}")
    # message(STATUS "glm_DIR: ${glm_DIR}")
    # message(STATUS "GTest_DIR: ${GTest_DIR}")
    message(STATUS "CUSTOM LIBRARY PATHS SET.")
endif()

if(MPE_ANGLE)
    if(VERBOSE)
        message(STATUS "ADDING ANGLE DEPENDENCY...")
    endif()

    set(angle_DIR ${VENDOR_DIR}/angle)
    set(angle_Include ${angle_DIR}/include)
    set(angle_Lib ${angle_DIR}/out/Release)

    include_directories(${angle_Include})
    link_directories(${angle_Lib})

    find_library(ANGLE_GLESv2_LIBRARY libGLESv2.dylib PATHS ${angle_Lib})
    find_library(ANGLE_EGL_LIBRARY libEGL.dylib PATHS ${angle_Lib})

    if(MPE_ANDROID_BUILD)
        set(ANGLE_DLLS
            # ${angle_Lib}/libGLESv2.dll
            # ${angle_Lib}/libEGL.dll
            # ${angle_Lib}/libc++.dll
            # ${angle_Lib}/third_party_abseil-cpp_absl.dll
            # ${angle_Lib}/third_party_zlib.dll
            # ${angle_Lib}/dawn_proc.dll
            # ${angle_Lib}/dawn_native.dll
            # ${angle_Lib}/dawn_platform.dll
        )
    else()
        set(ANGLE_DLLS
            ${angle_Lib}/libGLESv2.dylib
            ${angle_Lib}/libEGL.dylib
            # ${angle_Lib}/libc++.dll
            # ${angle_Lib}/third_party_zlib.dll
            # ${angle_Lib}/third_party_abseil-cpp_absl.dll
            # ${angle_Lib}/dawn_proc.dll
            # ${angle_Lib}/dawn_native.dll
            # ${angle_Lib}/dawn_platform.dll
        )
    endif(MPE_ANDROID_BUILD)
endif(MPE_ANGLE)