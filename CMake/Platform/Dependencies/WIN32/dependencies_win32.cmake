set(USE_VCPKG ON)

if(${VERBOSE})
    message("
-----------------------------------------------------------
VCPKG STATUS: ${USE_VCPKG}\n")
endif()

# GET VCPKG TOOLCHAIN PATH
if(EXISTS ${VCPKG_TOOLCHAIN_PATH_FILE})
    file(READ ${VCPKG_TOOLCHAIN_PATH_FILE} VCPKG_ROOT_PATH_SETUP_OUTPUT)
    string(STRIP ${VCPKG_ROOT_PATH_SETUP_OUTPUT} VCPKG_ROOT_PATH_SETUP_OUTPUT)
    set(VCPKG_FILEPATH ${VCPKG_ROOT_PATH_SETUP_OUTPUT})
    message(STATUS "VCPKG TOOLCHAIN PATH: ${VCPKG_FILEPATH}")
else()
    message(FATAL_ERROR "VCPKG TOOLCHAIN PATH NOT FOUND: ${VCPKG_TOOLCHAIN_PATH_FILE}")
endif()

# GET VCPKG PATH
if(EXISTS ${VCPKG_ROOT_PATH_FILE})
    file(READ ${VCPKG_ROOT_PATH_FILE} VCPKG_ROOT_PATH_OUTPUT)
    string(STRIP ${VCPKG_ROOT_PATH_OUTPUT} VCPKG_ROOT_PATH_OUTPUT)
    set(VCPKG_ROOT_PATH ${VCPKG_ROOT_PATH_OUTPUT})
    message(STATUS "VCPKG PATH: ${VCPKG_ROOT_PATH}")
else()
    message(FATAL_ERROR "VCPKG PATH NOT FOUND: ${VCPKG_ROOT_PATH_FILE}")
endif()

file(TO_CMAKE_PATH "${VCPKG_FILEPATH}/installed/x64-windows" VCPKG_CORE)

if(NOT EXISTS "${VCPKG_FILEPATH}")
    message(
        FATAL_ERROR
        "VCPKG NOT FOUND - MAKE SURE \"${VCPKG_FILEPATH}\" IS SET CORRECTLY.\nCURRENT PATH IS SET TO: \"${VCPKG_FILEPATH}\"."
    )
endif()

if(USE_VCPKG)
    if(${VERBOSE})
        message(
            STATUS
            "LOOKING FOR VCPKG CMAKE FILE IN \"${VCPKG_FILEPATH}\" TO MANAGE DEPENDENCIES")
    endif()

    # set(X_VCPKG_APPLOCAL_DEPS_INSTALL ON)
    set(CMAKE_TOOLCHAIN_FILE
        "${VCPKG_FILEPATH}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
    set(CMAKE_PREFIX_PATH "${VCPKG_FILEPATH}/installed/x64-windows")

    if(${VERBOSE})
        message("
VCPKG FOUND.
-----------------------------------------------------------")
    endif()
endif()

# USE SPECIFIC PATHS FOR VCPKG LIBRARIES
set(VCPKG_CUSTOM_PATHS ON)

if(${VERBOSE})
    message("
-----------------------------------------------------------
VCPKG CUSTOM PATHS STATUS: ${VCPKG_CUSTOM_PATHS}\n")
endif()

if(${VCPKG_CUSTOM_PATHS})
    if(${VERBOSE})
        message(STATUS "VCPKG SETTING CUSTOM PATHS...")
    endif()

    # SETTING FMT
    set(fmt_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\fmt")
    set(spdlog_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\spdlog")

    # SETTING GLAD
    set(glad_DIR "${UNIVERSAL_VENDOR_DIR}/glad")

    file(GLOB_RECURSE GLAD_S
        "${glad_DIR}/src/glad.c"
    )

    add_library(glad STATIC ${GLAD_S})
    target_include_directories(glad PUBLIC "${glad_DIR}/include")

    # SETTING GLFW3
    set(glfw3_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\glfw3")

    # SETTING IMGUI

    # set(imgui_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\imgui")
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

    # SETTING GLM
    set(glm_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\glm")
    set(GTest_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\gtest")

    # SETTING STB
    set(Stb_DIR ${UNIVERSAL_VENDOR_DIR}/stb)
    add_library(Stb INTERFACE
        "${Stb_DIR}"
    )
    target_include_directories(Stb INTERFACE
        "${Stb_DIR}"
    )

    # SETTING OPENCV
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(OpenCV_DIR ${VENDOR_DIR}/opencv/Install/Debug)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(OpenCV_DIR ${VENDOR_DIR}/opencv/Install/Release)
    endif()

    file(GLOB_RECURSE OpenCV_DLLs
        ${OpenCV_DIR}/x64/vc17/bin/*.dll)

    find_package(OpenCV REQUIRED)

    if(${VERBOSE})
        message("
...........................................................
* fmt_DIR: ${fmt_DIR}
* spdlog_DIR: ${spdlog_DIR}
* glad_DIR: ${glad_DIR}
* glfw3_DIR: ${glfw3_DIR}
* imgui_DIR: ${imgui_DIR}
* glm_DIR: ${glm_DIR}
* GTest_DIR: ${GTest_DIR}
* Stb_DIR: ${Stb_DIR}
* OpenCV_DIR: ${OpenCV_DIR}
...........................................................")

        # message(STATUS "OpenCV DLLs: ${OpenCV_DLLs}")
        message("
VCPKG SETTING CUSTOM PATHS SET

VCPKG SETUP COMPLETE
-----------------------------------------------------------\n")
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

        find_library(ANGLE_GLESv2_LIBRARY libGLESv2.dll.lib PATHS ${angle_Lib})
        find_library(ANGLE_EGL_LIBRARY libEGL.dll.lib PATHS ${angle_Lib})

        if(MPE_ANDROID_BUILD)
            set(ANGLE_DLLS
                ${angle_Lib}/libGLESv2.dll
                ${angle_Lib}/libEGL.dll
                ${angle_Lib}/libc++.dll
                ${angle_Lib}/third_party_abseil-cpp_absl.dll
                ${angle_Lib}/third_party_zlib.dll
                ${angle_Lib}/dawn_proc.dll
                ${angle_Lib}/dawn_native.dll
                ${angle_Lib}/dawn_platform.dll
            )
        else()
            set(ANGLE_DLLS
                ${angle_Lib}/libGLESv2.dll
                ${angle_Lib}/libEGL.dll
                ${angle_Lib}/libc++.dll
                ${angle_Lib}/third_party_zlib.dll
                ${angle_Lib}/third_party_abseil-cpp_absl.dll
                ${angle_Lib}/dawn_proc.dll
                ${angle_Lib}/dawn_native.dll
                ${angle_Lib}/dawn_platform.dll
            )
        endif(MPE_ANDROID_BUILD)
    endif(MPE_ANGLE)
endif()