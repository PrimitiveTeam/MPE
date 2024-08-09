# find_package(fmt CONFIG REQUIRED)

# find_package(spdlog CONFIG REQUIRED)

# find_package(PkgConfig REQUIRED)
# pkg_check_modules(FMT REQUIRED fmt)

# if(FMT_FOUND)
# include_directories(${FMT_INCLUDE_DIRS})
# link_directories(${FMT_LIBRARY_DIRS})
# add_definitions(${FMT_CFLAGS_OTHER})
# message(STATUS "Found fmt: ${FMT_LIBRARIES}")
# else()
# message(FATAL_ERROR "fmt library not found")
# endif()

# pkg_check_modules(SPDLOG REQUIRED spdlog)

# if(SPDLOG_FOUND)
# include_directories(${SPDLOG_INCLUDE_DIRS})
# link_directories(${SPDLOG_LIBRARY_DIRS})
# add_definitions(${SPDLOG_CFLAGS_OTHER})
# message(STATUS "Found spdlog: ${SPDLOG_LIBRARIES}")
# else()
# message(FATAL_ERROR "spdlog library not found")
# endif()

# pkg_check_modules(GLM REQUIRED glm)

# if(GLM_FOUND)
# include_directories(${GLM_INCLUDE_DIRS})
# link_directories(${GLM_LIBRARY_DIRS})
# add_definitions(${GLM_CFLAGS_OTHER})
# message(STATUS "Found glm: ${GLM_LIBRARIES}")
# else()
# message(FATAL_ERROR "glm library not found")
# endif()

if(MPE_USE_X11)
    find_package(X11 REQUIRED)
endif()

if(MPE_USE_WAYLAND)
    find_package(Wayland REQUIRED)
endif()

if(MPE_USE_X11)
    if(${VERBOSE})
        message("
***********************************************************
  * X11
***********************************************************")
    endif()
elseif(MPE_USE_WAYLAND)
    if(${VERBOSE})
        message("
***********************************************************
  * Wayland
***********************************************************")
    endif()
endif()