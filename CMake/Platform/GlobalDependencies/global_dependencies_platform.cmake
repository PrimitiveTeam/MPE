if(COMPILATION_PLATFORM STREQUAL "WIN32")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/GlobalDependencies/WIN32/global_dependencies_win32.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
    # DO AN ADDITIONAL CHECK FOR X11 AND WAYLAND - MOST LIKELY CAN'T BE USED TOGETHER
    if(MPE_USE_X11 AND MPE_USE_WAYLAND)
        message(FATAL_ERROR "X11 AND WAYLAND CAN'T BE USED TOGETHER.")
    endif()

    include("${PROJECT_SOURCE_DIR}/CMake/Platform/GlobalDependencies/UNIX/global_dependencies_unix.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "OSX")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/GlobalDependencies/OSX/global_dependencies_osx.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/GlobalDependencies/RPI4/global_dependencies_rpi4.cmake")
else()
    message(FATAL_ERROR "${COMPILATION_PLATFORM} NOT SUPPORTED.")
endif()

# find_package(imguizmo CONFIG REQUIRED) find_package(yaml-cpp CONFIG REQUIRED)
# find_package(Stb REQUIRED)