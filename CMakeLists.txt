cmake_minimum_required(VERSION 3.28)

# TOGGLE TESTING
set(MAIN_TEST OFF)

# TOGGLE EXAMPLES
set(EXAMPLES OFF)

# TOGGLE .DLL IN INSTALLS
set(INSTALL_DLLS OFF)

# SWITCHES FOR PROJECTS
set(MPE_PROJECTS ON)
set(MPE_PROJECT_SANDBOX OFF)
set(MPE_PROJECT_PONG ON)
set(MPE_PROJECT_PROJECTPICKER OFF)
set(MPE_PROJECT_OPENCVTEST OFF)

# ANGLE
set(MPE_ANGLE ON)

# TEMPORARY
# DUMMY EXECUTABLE
set(DUMMY_EXECUTABLE ON)

# SHARED OR STATIC LIBRARY
# ONLY 'STATIC' OR 'SHARED'
set(MPE_LIBRARY_TYPE SHARED)

# SETTING PROJECT VERSION
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 1)
set(PROJECT_VERSION_SUFFIX "a")
set(PROJECT_VERSION
  ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}
)
set(PROJECT_FULL_VERSION
  ${PROJECT_VERSION_MAJOR}${PROJECT_VERSION_MINOR}${PROJECT_VERSION_PATCH}${PROJECT_VERSION_TWEAK}${PROJECT_VERSION_SUFFIX}
)

# CREATING PROJECT
if(WIN32)
  project(MERELY_PRIMITIVE_ENGINE VERSION ${PROJECT_VERSION} LANGUAGES C CXX)
elseif(APPLE)
  project(MERELY_PRIMITIVE_ENGINE VERSION ${PROJECT_VERSION} LANGUAGES C CXX OBJC OBJCXX)
else()
  project(MERELY_PRIMITIVE_ENGINE VERSION ${PROJECT_VERSION} LANGUAGES C CXX)
endif()

set(BUILD_TYPE_FILE "${PROJECT_SOURCE_DIR}/Artifacts/.BUILD_TYPE")
set(CROSS_COMPILE_FILE "${PROJECT_SOURCE_DIR}/Artifacts/.CROSS_COMPILE_TARGET")
set(VCPKG_ROOT_PATH_FILE "${PROJECT_SOURCE_DIR}/Artifacts/.VCPKG_ROOT_PATH")
set(VCPKG_TOOLCHAIN_PATH_FILE "${PROJECT_SOURCE_DIR}/Artifacts/.VCPKG_TOOLCHAIN_PATH")

# DETECT BUILD TYPE
if(EXISTS ${BUILD_TYPE_FILE})
  file(READ ${BUILD_TYPE_FILE} BUILD_TYPE_SETUP_OUTPUT)
  string(STRIP ${BUILD_TYPE_SETUP_OUTPUT} BUILD_TYPE_SETUP_OUTPUT)
  set(CMAKE_BUILD_TYPE ${BUILD_TYPE_SETUP_OUTPUT})
  message(STATUS "DETECTED BUILD TYPE: ${CMAKE_BUILD_TYPE}")
else()
  message(FATAL_ERROR "BUILD TYPE NOT DETECTED: ${BUILD_TYPE_FILE}")
endif()

# DETECT CROSS-COMPILATION
if(EXISTS ${CROSS_COMPILE_FILE})
  file(READ ${CROSS_COMPILE_FILE} CROSS_COMPILATION_TARGET_OUTPUT)
  string(STRIP ${CROSS_COMPILATION_TARGET_OUTPUT} CROSS_COMPILATION_TARGET_OUTPUT)
  set(CROSS_COMPILATION_TARGET ${CROSS_COMPILATION_TARGET_OUTPUT})

  # IF EMPTY THEN SET CROSS_COMPILATION TO OFF
  if(CROSS_COMPILATION_TARGET STREQUAL "")
    set(CROSS_COMPILATION OFF)
    cmake_minimum_required(VERSION 3.28)
    set(CMAKE_CXX_STANDARD 23)
  else()
    set(CROSS_COMPILATION ON)
    cmake_minimum_required(VERSION 3.22.1)
    set(CMAKE_CXX_STANDARD 17)
  endif()
else()
  message(STATUS "CROSS-COMPILATION NOT DETECTED.")
  set(CROSS_COMPILATION OFF)
endif()

if(CROSS_COMPILATION)
  message(STATUS "CROSS COMPILATION: ${CROSS_COMPILATION_TARGET}")
endif()

set(CXX_VERSION_NAME "cxx_std_${CMAKE_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SET AVAILABLE BUILD TYPES TO DEBUG AND RELEASE
# TODO: OpenCV throws generation errors if other build types are used
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# SET INSTALLATION PATH CoreD ON BUILD TYPE SETTING BUILD TYPE TOGGLING CUSTOM
# VERBOSITY
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(INSTALL_PATH_SUFFIX "Debug")
  set(CMAKE_BUILD_TYPE Debug)
  set(VERBOSE
    ON
    CACHE INTERNAL "Verbosity on")
  set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(INSTALL_PATH_SUFFIX "Release")
  set(CMAKE_BUILD_TYPE Release)
  set(VERBOSE
    OFF
    CACHE INTERNAL "Verbosity off")
  set(CMAKE_EXPORT_COMPILE_COMMANDS FALSE)
else()
  set(INSTALL_PATH_SUFFIX "Unknown")
  set(VERBOSE
    ON
    CACHE INTERNAL "Verbosity on")
  message(FATAL_ERROR "UNKNOWN BUILD TYPE: \"${CMAKE_BUILD_TYPE}\".")
endif()

if(${VERBOSE})
  message("
-----------------------------------------------------------
* PROJECT NAME: ${PROJECT_NAME}
* PROJECT VERSION: ${PROJECT_VERSION}
* PROJECT FULL VERSION: ${PROJECT_FULL_VERSION}
-----------------------------------------------------------")
endif()

# PATH TO INSTALLATION DIRECTORY
set(CMAKE_INSTALL_PREFIX
  "${CMAKE_CURRENT_SOURCE_DIR}/Install/${CMAKE_BUILD_TYPE}"
  CACHE PATH "Installation Directory" FORCE)

if(${VERBOSE})
  message("
-----------------------------------------------------------
* DEFAULT INSTALLATION DIRECTORY: \"${CMAKE_INSTALL_PREFIX}\"
-----------------------------------------------------------\n")
endif()

# CHECKING PLATFORM
string(TOUPPER "${CMAKE_SYSTEM_NAME}" CURRENT_PLATFORM)

# DOUBLE CHECKS IF THE SYSTEM IS RUNNING ON X64 SYSTEM THIS ALSO FAILS IF THE
# COMPILER IS NOT 64-BIT COMPATIBLE
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(STATUS "SIZE OF VOID POINTER: ${CMAKE_SIZEOF_VOID_P}")

  if(CROSS_COMPILATION)
    message("
-----------------------------------------------------------
MPE DOES NOT OFFICIALLY SUPPORT NON X64 SYSTEMS.
-----------------------------------------------------------\n")
  else()
    message(FATAL_ERROR "MPE SUPPORTS X64 SYSTEMS ONLY.")
    return()
  endif()
endif()

# SETTING UP COMPILER
if(${VERBOSE})
  message(STATUS "SETTING UP COMPILER...")
endif()

if(${CROSS_COMPILATION})
  string(TOLOWER "${CROSS_COMPILATION_TARGET}" LOVER_CROSS_COMPILATION_TARGET)

  if(LOVER_CROSS_COMPILATION_TARGET STREQUAL "rpi4")
    set(CURRENT_COMPILER "GNU")
    set(COMPILATION_PLATFORM "RPI4")
  else()
    message(FATAL_ERROR "COMPILER: {${CMAKE_CXX_COMPILER_ID}} NOT SUPPORTED.")
  endif()

  # DEBUGGING FOR CROSS-COMPILATION
  message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
  execute_process(
    COMMAND ${CMAKE_C_COMPILER} --version
    OUTPUT_VARIABLE C_COMPILER_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  message(STATUS "C Compiler version: ${C_COMPILER_VERSION}")

  message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} --version
    OUTPUT_VARIABLE CXX_COMPILER_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  message(STATUS "C++ Compiler version: ${CXX_COMPILER_VERSION}")
else()
  string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" LOWER_COMPILER_ID)

  if(LOWER_COMPILER_ID STREQUAL "msvc")
    set(CURRENT_COMPILER "MSVC")
    set(COMPILATION_PLATFORM "WIN32")
  elseif(LOWER_COMPILER_ID STREQUAL "gnu")
    set(CURRENT_COMPILER "GNU")
    set(COMPILATION_PLATFORM "UNIX")
  elseif(LOWER_COMPILER_ID STREQUAL "clang")
    set(CURRENT_COMPILER "CLANG")
    set(COMPILATION_PLATFORM "UNIX")
  elseif(LOWER_COMPILER_ID STREQUAL "appleclang")
    set(CURRENT_COMPILER "APPLECLANG")
    set(COMPILATION_PLATFORM "OSX")
  else()
    message(FATAL_ERROR "COMPILER: {${CMAKE_CXX_COMPILER_ID}} NOT SUPPORTED.")
  endif()
endif(${CROSS_COMPILATION})

if(${VERBOSE})
  message("
-----------------------------------------------------------
* CURRENT COMPILER PATH: ${CMAKE_CXX_COMPILER}
* CURRENT COMPILER: ${CURRENT_COMPILER}
* CURRENT COMPILER VERSION: ${CMAKE_CXX_COMPILER_VERSION}
* CURRENT PLATFORM: ${COMPILATION_PLATFORM}
* CURRENT SYSTEM: ${CURRENT_PLATFORM}
* COMPILER SETUP COMPLETE.
-----------------------------------------------------------")
endif(${VERBOSE})

set(VENDOR_DIR ${PROJECT_SOURCE_DIR}/Vendor/${COMPILATION_PLATFORM})
set(UNIVERSAL_VENDOR_DIR ${PROJECT_SOURCE_DIR}/Vendor/Universal)

message("
-----------------------------------------------------------
* CURRENT VENDOR DIRECTORY: ${VENDOR_DIR}
* UNIVERSAL VENDOR DIRECTORY: ${UNIVERSAL_VENDOR_DIR}
-----------------------------------------------------------")

# DEPENDENCY MANAGEMENT
if(WIN32)
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
        )
      else()
        set(ANGLE_DLLS
          ${angle_Lib}/libGLESv2.dll
          ${angle_Lib}/libEGL.dll
        )
      endif(MPE_ANDROID_BUILD)
    endif(MPE_ANGLE)
  endif()

elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
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

elseif(COMPILATION_PLATFORM STREQUAL "OSX")
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

elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
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

else()
  message(FATAL_ERROR "${COMPILATION_PLATFORM} NOT SUPPORTED.")
endif()

if(COMPILATION_PLATFORM STREQUAL "UNIX" OR COMPILATION_PLATFORM STREQUAL "RPI4")
  message("
-----------------------------------------------------------
HARD SETTINGS LIBRARY AS STATIC ON UNIX SYSTEMS DUE TO FAILURE OF IMGUI
-----------------------------------------------------------\n")
  set(MPE_LIBRARY_TYPE STATIC)
endif(COMPILATION_PLATFORM STREQUAL "UNIX" OR COMPILATION_PLATFORM STREQUAL "RPI4")

if(COMPILATION_PLATFORM STREQUAL "RPI4")
  message("
-----------------------------------------------------------
SETTING CMAKE_PREFIX_PATH TO '/usr/local'
-----------------------------------------------------------\n")

  # set(CMAKE_PREFIX_PATH "/usr/local")
endif(COMPILATION_PLATFORM STREQUAL "RPI4")

# ADDING DEPENDENCIES
if(${VERBOSE})
  message("
-----------------------------------------------------------
LOOKING FOR GLOBAL DEPENDENCIES...
-----------------------------------------------------------")
endif()

# FIND DEPENDCIES PROVIDED BY DEPENDENCY MANAGER
# WIN OSX UNIX
if(COMPILATION_PLATFORM STREQUAL "WIN32")
  find_package(fmt CONFIG REQUIRED)
  find_package(spdlog CONFIG REQUIRED)
  find_package(glfw3 CONFIG REQUIRED)
  find_package(glm CONFIG REQUIRED)

  if(${VERBOSE})
    message("
***********************************************************
  * fmt
  * spdlog
  * glfw3
  * glm
***********************************************************")
  endif()
endif(COMPILATION_PLATFORM STREQUAL "WIN32")

if(COMPILATION_PLATFORM STREQUAL "UNIX")
  find_package(fmt CONFIG REQUIRED)
  find_package(spdlog CONFIG REQUIRED)
  find_package(glfw3 CONFIG REQUIRED)
  find_package(glm CONFIG REQUIRED)

  if(${VERBOSE})
    message("
***********************************************************
  * fmt
  * spdlog
  * glfw3
  * glm
***********************************************************")
  endif()
endif(COMPILATION_PLATFORM STREQUAL "UNIX")

if(COMPILATION_PLATFORM STREQUAL "OSX")
  find_package(fmt CONFIG REQUIRED)
  find_package(spdlog CONFIG REQUIRED)
  find_package(glfw3 CONFIG REQUIRED)
  find_package(glm CONFIG REQUIRED)
  find_library(COCOA_LIBRARY Cocoa)

  if(${VERBOSE})
    message("
***********************************************************
  * fmt
  * spdlog
  * glfw3
  * glm
  * COCOA
***********************************************************")
  endif()
endif(COMPILATION_PLATFORM STREQUAL "OSX")

# EXPLICITLY SET PACKAGE_DIR FOR RPI4
if(COMPILATION_PLATFORM STREQUAL "RPI4")
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
endif(COMPILATION_PLATFORM STREQUAL "RPI4")

if(COMPILATION_PLATFORM STREQUAL "OSX")
endif()

# find_package(imguizmo CONFIG REQUIRED) find_package(yaml-cpp CONFIG REQUIRED)
# find_package(Stb REQUIRED)
if(${VERBOSE})
  message("
-----------------------------------------------------------
ALL DEPENDENCIES FOUND
-----------------------------------------------------------")
endif()

# ADDING TESTING ENVIRONMENT
if(${VERBOSE})
  message("
-----------------------------------------------------------
ADDING TESTING ENVIRONMENT...
")
endif()

include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_FULL_VERSION})
include(CPack)

message(
  STATUS
  "CTEST/CPACK STATUS: \"${CPACK_PROJECT_NAME}\" VERSION \"${CPACK_PROJECT_VERSION}\"."
)

if(${VERBOSE})
  message("
TESTING ENVIRONMENT ADDED
-----------------------------------------------------------")
endif()

# ADD SOURCE FILES MPE LIBRARY .CPP FILES
file(
  GLOB_RECURSE
  MPE_CPP

  # TEST
  "${PROJECT_SOURCE_DIR}/MPE/Test/Test.cpp"

  # /Core
  "${PROJECT_SOURCE_DIR}/MPE/Core/_PTRS.cpp"

  # /Log
  "${PROJECT_SOURCE_DIR}/MPE/Log/Log.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Log/GlobalLog.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Log/CustomSinks/MemorySink.cpp"

  # /Errors
  "${PROJECT_SOURCE_DIR}/MPE/Errors/Error.cpp"

  # /App
  "${PROJECT_SOURCE_DIR}/MPE/App/App.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/App/Window.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/App/WindowProps.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/App/Layers/Layer.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/App/Layers/LayerStack.cpp"

  # /Profiling
  "${PROJECT_SOURCE_DIR}/MPE/Profiling/_PROFILING.cpp"

  # /Physics
  "${PROJECT_SOURCE_DIR}/MPE/Time/Time.cpp"

  # /Input
  "${PROJECT_SOURCE_DIR}/MPE/Input/KeyState.cpp"

  # /Events
  "${PROJECT_SOURCE_DIR}/MPE/Events/EventApp.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Events/EventFunction.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Events/EventGraphics.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Events/EventKey.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Events/EventMouse.cpp"

  # /Renderer
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Renderer.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Renderer2D.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/RendererAPI.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/RendererUtilities.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderPrimitive.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderSettings.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/OrthographicCamera.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/OrthographicCameraController.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/StaticOrthographicCamera.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/BufferLayout.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/IndexBuffer.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/VertexArray.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/VertexBuffer.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderInformation/RenderInfo.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/Shader.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/ShaderLibrary.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture2D.cpp"

  # /Editor
  "${PROJECT_SOURCE_DIR}/MPE/Editor/Grid/Grid.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Editor/Dialog/SimpleDialog.cpp"

  # /Platform/OpenGL
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLContext.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLContextProps.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLRendererAPI.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLSettings.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Editor/Grid/OpenGLGrid.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLIndexBuffer.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLVertexArray.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLVertexBuffer.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Shaders/OpenGLShader.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Textures/OpenGLTexture.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Textures/OpenGLTexture2D.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Utilities/OpenGLUtilities.cpp"

  # /Platform/OpenGLES
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESContext.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESContextProps.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESRendererAPI.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESSettings.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Editor/Grid/OpenGLESGrid.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESIndexBuffer.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESVertexArray.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESVertexBuffer.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Shaders/OpenGLESShader.cpp"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Textures/OpenGLESTexture.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Textures/OpenGLESTexture2D.cpp"

  # /Vendor
  "${PROJECT_SOURCE_DIR}/MPE/Vendor/ImGui/ImGuiLayer.cpp"
  "${PROJECT_SOURCE_DIR}/MPE/Vendor/STB/stb_image_impl.cpp"
)

# MPE LIBRARY .H FILES
file(
  GLOB_RECURSE
  MPE_H

  # TEST
  "${PROJECT_SOURCE_DIR}/MPE/Test/Test.h"

  # /
  "${PROJECT_SOURCE_DIR}/MPE/EntryPoint.h"
  "${PROJECT_SOURCE_DIR}/MPE/MPE.h"
  "${PROJECT_SOURCE_DIR}/MPE/MPEPCH.h"
  "${PROJECT_SOURCE_DIR}/MPE/MPEPLAT.h"

  # /Core
  "${PROJECT_SOURCE_DIR}/MPE/Core/_ASSERTS.h"
  "${PROJECT_SOURCE_DIR}/MPE/Core/_CORE.h"
  "${PROJECT_SOURCE_DIR}/MPE/Core/_CWD.h"
  "${PROJECT_SOURCE_DIR}/MPE/Core/_INIT.h"
  "${PROJECT_SOURCE_DIR}/MPE/Core/_PTRS.h"

  # /Log
  "${PROJECT_SOURCE_DIR}/MPE/Log/Log.h"
  "${PROJECT_SOURCE_DIR}/MPE/Log/GlobalLog.h"
  "${PROJECT_SOURCE_DIR}/MPE/Log/CustomSinks/MemorySink.h"

  # /Errors
  "${PROJECT_SOURCE_DIR}/MPE/Errors/Error.h"
  "${PROJECT_SOURCE_DIR}/MPE/Errors/Errors.h"

  # /App
  "${PROJECT_SOURCE_DIR}/MPE/App/App.h"
  "${PROJECT_SOURCE_DIR}/MPE/App/Window.h"
  "${PROJECT_SOURCE_DIR}/MPE/App/WindowProps.h"
  "${PROJECT_SOURCE_DIR}/MPE/App/Layers/Layer.h"
  "${PROJECT_SOURCE_DIR}/MPE/App/Layers/LayerStack.h"

  # /Profiling
  "${PROJECT_SOURCE_DIR}/MPE/Profiling/_PROFILING.h"
  "${PROJECT_SOURCE_DIR}/MPE/Profiling/_TIMER.h"

  # /Physics
  "${PROJECT_SOURCE_DIR}/MPE/Time/Time.h"

  # /Input
  "${PROJECT_SOURCE_DIR}/MPE/Input/Input.h"
  "${PROJECT_SOURCE_DIR}/MPE/Input/KeyCodes.h"
  "${PROJECT_SOURCE_DIR}/MPE/Input/KeyState.h"
  "${PROJECT_SOURCE_DIR}/MPE/Input/MouseButtonCodes.h"

  # /Events
  "${PROJECT_SOURCE_DIR}/MPE/Events/Event.h"
  "${PROJECT_SOURCE_DIR}/MPE/Events/EventApp.h"
  "${PROJECT_SOURCE_DIR}/MPE/Events/EventFunction.h"
  "${PROJECT_SOURCE_DIR}/MPE/Events/EventGraphics.h"
  "${PROJECT_SOURCE_DIR}/MPE/Events/EventKey.h"
  "${PROJECT_SOURCE_DIR}/MPE/Events/EventMouse.h"

  # /Renderer
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/GraphicalContext.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/GraphicalContextProps.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Renderer.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Renderer2D.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/RendererAPI.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/RendererUtilities.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderPrimitive.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderSettings.h"

  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/OrthographicCamera.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/OrthographicCameraController.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Cameras/StaticOrthographicCamera.h"

  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/BufferLayout.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/IndexBuffer.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/VertexArray.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Pipeline/VertexBuffer.h"

  "${PROJECT_SOURCE_DIR}/MPE/Renderer/RenderInformation/RenderInfo.h"

  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/Shader.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Shaders/ShaderLibrary.h"

  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture.h"
  "${PROJECT_SOURCE_DIR}/MPE/Renderer/Textures/Texture2D.h"

  # /Editor
  "${PROJECT_SOURCE_DIR}/MPE/Editor/Grid/Grid.h"

  "${PROJECT_SOURCE_DIR}/MPE/Editor/Dialog/SimpleDialog.h"

  # /Platform/OpenGL
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLContext.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLContextProps.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLRendererAPI.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/OpenGLSettings.h"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Editor/Grid/OpenGLGrid.h"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLIndexBuffer.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLVertexArray.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Pipeline/OpenGLVertexBuffer.h"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Shaders/OpenGLShader.h"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Textures/OpenGLTexture.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Textures/OpenGLTexture2D.h"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGL/Utilities/OpenGLUtilities.h"

  # /Platform/OpenGLES
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESContext.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESContextProps.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESRendererAPI.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/OpenGLESSettings.h"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Editor/Grid/OpenGLESGrid.h"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESIndexBuffer.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESVertexArray.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Pipeline/OpenGLESVertexBuffer.h"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Shaders/OpenGLESShader.h"

  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Textures/OpenGLESTexture.h"
  "${PROJECT_SOURCE_DIR}/MPE/Platform/OpenGLES/Textures/OpenGLESTexture2D.h"

  # /Vendor
  "${PROJECT_SOURCE_DIR}/MPE/Vendor/ImGui/ImGuiLayer.h"
  "${PROJECT_SOURCE_DIR}/MPE/Vendor/STB/stb_image.h"
)

# PRINT MPE SOURCE FILES
if(${VERBOSE})
  # message("
  # -----------------------------------------------------------
  # MPE HEADERS AND SOURCE FILES
  # -----------------------------------------------------------")
  message("
-----------------------------------------------------------
MPE HEADERS AND SOURCE FILES")

  message("
***********************************************************

CORE SOURCE FILES:\n")

  foreach(MPE_CPP_FILE ${MPE_CPP})
    message("${MPE_CPP_FILE}")
  endforeach()

  message("
CORE HEADER FILES:\n")

  foreach(MPE_H_FILE ${MPE_H})
    message("${MPE_H_FILE}")
  endforeach()

  message("
***********************************************************")
endif()

# ADD PLATFORM BASED MPE SOURCE FILES
if(COMPILATION_PLATFORM STREQUAL "WIN32")
  file(
    GLOB_RECURSE
    MPE_WIN32_CPP

    # /Platform/Windows/Core
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/Core/*.cpp"

    # /Platform/Windows/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/App/*.cpp"

    # /Platform/Windows/Errors
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/Errors/*.cpp"

    # /Platform/Windows/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/Input/*.cpp"

    # /Platform/Windows/Editor/Prompts
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/Editor/Prompts/*.cpp"
  )

  file(
    GLOB_RECURSE
    MPE_WIN32_H

    # /Platform/Windows/Core
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/Core/*.h"

    # /Platform/Windows/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/App/*.h"

    # /Platform/Windows/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Windows/Input/*.h"
  )

  # ADD MPE WIN32 SOURCE FILES
  list(APPEND MPE_CPP ${MPE_WIN32_CPP})

  list(APPEND MPE_H ${MPE_WIN32_H})

  # PRINT MPE WIN32 SOURCE FILES
  if(${VERBOSE})
    message("
MPE WIN32 SOURCE AND HEADER FILES

WIN32 SOURCE FILES:\n")

    foreach(MPE_WIN32_CPP_FILE ${MPE_WIN32_CPP})
      message("${MPE_WIN32_CPP_FILE}")
    endforeach()

    message("
WIN32 HEADER FILES:\n")

    foreach(MPE_WIN32_H_FILE ${MPE_WIN32_H})
      message("${MPE_WIN32_H_FILE}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()
elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
  file(
    GLOB_RECURSE
    MPE_Linux_CPP

    # /Platform/Linux/Core
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Core/*.cpp"

    # /Platform/Linux/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/App/*.cpp"

    # /Platform/Linux/Errors
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Errors/*.cpp"

    # /Platform/Linux/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Input/*.cpp"
  )

  file(
    GLOB_RECURSE
    MPE_Linux_H

    # /Platform/Linux/Core
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Core/*.h"

    # /Platform/Linux/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/App/*.h"

    # /Platform/Linux/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/Linux/Input/*.h"
  )

  # ADD MPE Linux SOURCE FILES
  list(APPEND MPE_CPP ${MPE_Linux_CPP})

  list(APPEND MPE_H ${MPE_Linux_H})

  # PRINT MPE Linux SOURCE FILES
  if(${VERBOSE})
    message("
MPE LINUX SOURCE AND HEADER FILES

LINUX SOURCE FILES:\n")

    foreach(MPE_LINUX_CPP_FILE ${MPE_LINUX_CPP})
      message("${MPE_LINUX_CPP_FILE}")
    endforeach()

    message("
LINUX HEADER FILES:\n")

    foreach(MPE_LINUX_H_FILE ${MPE_LINUX_H})
      message("${MPE_LINUX_H_FILE}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()
elseif(COMPILATION_PLATFORM STREQUAL "OSX")
  file(
    GLOB_RECURSE
    MPE_macOS_CPP

    # /Platform/macOS/Core
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Core/*.mm"

    # /Platform/macOS/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/App/*.cpp"

    # /Platform/macOS/Errors
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Errors/*.mm"

    # /Platform/macOS/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Input/*.cpp"
  )

  file(
    GLOB_RECURSE
    MPE_macOS_H

    # /Platform/macOS/Core
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Core/*.h"

    # /Platform/macOS/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/App/*.h"

    # /Platform/macOS/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/macOS/Input/*.h"
  )

  # ADD MPE macOS SOURCE FILES
  list(APPEND MPE_CPP ${MPE_macOS_CPP})

  list(APPEND MPE_H ${MPE_macOS_H})

  # set_source_files_properties(${MPE_OSX_CPP} PROPERTIES COMPILE_FLAGS "-include MPE/MPEPCH.h")

  # PRINT MPE macOS SOURCE FILES
  if(${VERBOSE})
    message("
MPE macOS SOURCE AND HEADER FILES

macOS SOURCE FILES:\n")

    foreach(MPE_macOS_CPP_FILE ${MPE_macOS_CPP})
      message("${MPE_macOS_CPP_FILE}")
    endforeach()

    message("
macOS HEADER FILES:\n")

    foreach(MPE_macOS_H_FILE ${MPE_macOS_H})
      message("${MPE_macOS_H_FILE}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

# HYPERSPECIFIC PLATFORMS
elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
  file(
    GLOB_RECURSE
    MPE_RPI4_CPP

    # /Platform/RPI/Core
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/Core/*.cpp"

    # /Platform/RPI/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/App/*.cpp"

    # /Platform/RPI/Errors
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/Errors/*.cpp"

    # /Platform/RPI/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/Input/*.cpp"
  )

  file(
    GLOB_RECURSE
    MPE_RPI4_H

    # /Platform/RPI/Core
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/Core/*.h"

    # /Platform/RPI/App
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/App/*.h"

    # /Platform/RPI/Input
    "${PROJECT_SOURCE_DIR}/MPE/Platform/RPI/Input/*.h"
  )

  # ADD MPE RPI SOURCE FILES
  list(APPEND MPE_CPP ${MPE_RPI4_CPP})

  list(APPEND MPE_H ${MPE_RPI4_H})

  # PRINT MPE RPI SOURCE FILES
  if(${VERBOSE})
    message("
MPE RPI4 SOURCE AND HEADER FILES

RPI4 SOURCE FILES:\n")

    foreach(MPE_RPI4_CPP_FILE ${MPE_RPI4_CPP})
      message("${MPE_RPI4_CPP_FILE}")
    endforeach()

    message("   
RPI4 HEADER FILES:\n")

    foreach(MPE_RPI4_H_FILE ${MPE_RPI4_H})
      message("${MPE_RPI4_H_FILE}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()
endif()

# BUILD MPE LIBRARY BASED ON SET LIBRARY TYPE
if(${MPE_LIBRARY_TYPE} STREQUAL STATIC)
  if(COMPILATION_PLATFORM STREQUAL "WIN32")
    add_library(MPE STATIC
      ${MPE_CPP}
      ${MPE_WIN32_CPP}
    )
  elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
    add_library(MPE STATIC
      ${MPE_CPP}
      ${MPE_Linux_CPP}
    )
  elseif(COMPILATION_PLATFORM STREQUAL "OSX")
    add_library(MPE STATIC
      ${MPE_CPP}
      ${MPE_OSX_CPP}
    )

  # HYPERSPECIFIC PLATFORMS
  elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
    add_library(MPE STATIC
      ${MPE_CPP}
      ${MPE_RPI4_CPP}
    )
  endif()

  target_compile_definitions(MPE PRIVATE MPE_STATIC_LIBRARY)
elseif(${MPE_LIBRARY_TYPE} STREQUAL SHARED)
  if(COMPILATION_PLATFORM STREQUAL "WIN32")
    add_library(MPE SHARED
      ${MPE_CPP}
      ${MPE_WIN32_CPP}
    )
  elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
    add_library(MPE SHARED
      ${MPE_CPP}
      ${MPE_UNIX_CPP}
    )
  elseif(COMPILATION_PLATFORM STREQUAL "OSX")
    add_library(MPE SHARED
      ${MPE_CPP}
      ${MPE_OSX_CPP}
    )
  elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
    message(FATAL_ERROR "SHARED LIBRARY NOT SUPPORTED ON RPI4.")
  endif()

  target_compile_definitions(MPE PUBLIC MPE_DYNAMIC_LIBRARY)
  target_compile_definitions(MPE PRIVATE MPE_BUILD_DLL)

else()
  message(FATAL_ERROR "LIBRARY TYPE {${MPE_LIBRARY_TYPE}} NOT SUPPORTED.")
endif()

# COMPILER DEFINITIONS FOR MPE
if(COMPILATION_PLATFORM STREQUAL "WIN32")
  target_compile_definitions(MPE PUBLIC MPE_PLATFORM_WINDOWS)

elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
  target_compile_definitions(MPE PUBLIC MPE_PLATFORM_LINUX)

elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
  target_compile_definitions(MPE PUBLIC MPE_PLATFORM_LINUX)
  target_compile_definitions(MPE PUBLIC MPE_PLATFORM_RPI4)

elseif(COMPILATION_PLATFORM STREQUAL "OSX")
  target_compile_definitions(MPE PUBLIC MPE_PLATFORM_OSX)
endif()

target_compile_definitions(MPE PUBLIC MPE_ENABLE_ASSERTS)
target_compile_definitions(MPE PUBLIC MPE_COMPILER_${CURRENT_COMPILER})

# ENABLE PROFILING FOR DEBUG BUILS
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  target_compile_definitions(MPE PUBLIC MPE_CORE_DEBUG_PROFILING)
  target_compile_definitions(MPE PUBLIC MPE_DEBUG_PROFILING)
  target_compile_definitions(MPE PUBLIC MPE_ENABLE_DEBUG_LOG)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

target_compile_definitions(MPE PUBLIC MPE_FULL_VERSION_${PROJECT_FULL_VERSION})

# CMAKE IS NOT INHERETING COMPILER FLAGS PROPERLY
set(MPE_PUBLIC_DEFINITIONS)

if(MPE_LIBRARY_TYPE STREQUAL SHARED)
  list(APPEND MPE_PUBLIC_DEFINITIONS MPE_DYNAMIC_LIBRARY)
else()
  list(APPEND MPE_PUBLIC_DEFINITIONS MPE_STATIC_LIBRARY)
endif()

if(COMPILATION_PLATFORM STREQUAL "WIN32")
  list(APPEND MPE_PUBLIC_DEFINITIONS MPE_PLATFORM_WINDOWS)
elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
  list(APPEND MPE_PUBLIC_DEFINITIONS MPE_PLATFORM_LINUX)
elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
  list(APPEND MPE_PUBLIC_DEFINITIONS MPE_PLATFORM_LINUX MPE_PLATFORM_RPI4)
elseif(COMPILATION_PLATFORM STREQUAL "OSX")
  list(APPEND MPE_PUBLIC_DEFINITIONS MPE_PLATFORM_OSX)
endif()

list(APPEND MPE_PUBLIC_DEFINITIONS MPE_ENABLE_ASSERTS)
list(APPEND MPE_PUBLIC_DEFINITIONS MPE_COMPILER_${CURRENT_COMPILER})

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  list(APPEND MPE_PUBLIC_DEFINITIONS MPE_CORE_DEBUG_PROFILING MPE_DEBUG_PROFILING MPE_ENABLE_DEBUG_LOG)
endif()

list(APPEND MPE_PUBLIC_DEFINITIONS MPE_FULL_VERSION_${PROJECT_FULL_VERSION})

if(${VERBOSE})
  get_target_property(DEFINITIONS_LIST MPE COMPILE_DEFINITIONS)
  message("
-----------------------------------------------------------
MPE COMPILE DEFINITIONS\n")

  foreach(DEFINITION ${DEFINITIONS_LIST})
    message(STATUS "${DEFINITION}")
  endforeach()

  message("
-----------------------------------------------------------")
endif()

target_compile_features(MPE PUBLIC ${CXX_VERSION_NAME})
set_target_properties(MPE PROPERTIES VERSION ${PROJECT_FULL_VERSION})

set_target_properties(MPE PROPERTIES OUTPUT_NAME "MPE")

# MAKE SURE TO INCLUDE LIBRARY DIRECTORIES
# target_include_directories(MPE
# PRIVATE "${glad_DIR}/include"
# PRIVATE "${imgui_DIR}"
# )
# if(${VERBOSE})
# # PRINT INCLUDE DIRECTORIES
# get_target_property(INCLUDE_DIRECTORIES MPE INCLUDE_DIRECTORIES)
# message(STATUS "MPE INCLUDE DIRECTORIES: ${INCLUDE_DIRECTORIES}")
# endif()

# ADD MPE DEPENDENCIES

# NOT EQUAL TO UNIX
if(COMPILATION_PLATFORM STREQUAL "WIN32" OR COMPILATION_PLATFORM STREQUAL "OSX" OR COMPILATION_PLATFORM STREQUAL "UNIX")
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
endif(COMPILATION_PLATFORM STREQUAL "WIN32" OR COMPILATION_PLATFORM STREQUAL "OSX" OR COMPILATION_PLATFORM STREQUAL "UNIX")

if(COMPILATION_PLATFORM STREQUAL "WIN32")
  target_link_libraries(
    MPE
    PRIVATE ${OpenCV_LIBS}
  )

  if(MPE_ANGLE)
    target_include_directories(MPE
      PRIVATE ${angle_Include}
    )

    target_link_libraries(
      MPE
      PRIVATE ${ANGLE_GLESv2_LIBRARY}
    )
  endif(MPE_ANGLE)
endif()

if(COMPILATION_PLATFORM STREQUAL "OSX")
  target_link_libraries(
    MPE
    PRIVATE ${COCOA_LIBRARY}
  )
endif()

if(COMPILATION_PLATFORM STREQUAL "RPI4")
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

    # CURRENTLY NOT IN USE: imguizmo::imguizmo yaml-cpp
  )
endif()

# find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
target_include_directories(MPE
  PRIVATE
  ${Stb_INCLUDE_DIRS}
)

if(COMPILATION_PLATFORM STREQUAL "WIN32")
  target_include_directories(MPE
    PRIVATE
    ${OpenCV_INCLUDE_DIRS}
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

if(COMPILATION_PLATFORM STREQUAL "UNIX" OR COMPILATION_PLATFORM STREQUAL "RPI4")
  target_include_directories(MPE
    PUBLIC "${GTK3_INCLUDE_DIRS}")
endif()

# target_include_directories(MPE PUBLIC
# "${PROJECT_SOURCE_DIR}/MPE/Vendor/STB")
if(COMPILATION_PLATFORM STREQUAL "WIN32")
  # INSTALLATION FOR LIBRARIES
  # EXAMPLES FOR FUTURE
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # MPE DEBUG DLLS
    set(MPE_DLL_FILES
      ${PROJECT_SOURCE_DIR}/Build/Debug/MPE.dll)
    set(DEPENENDENCY_DLL_FILES
      ${PROJECT_SOURCE_DIR}/Build/Debug/fmtd.dll
      ${PROJECT_SOURCE_DIR}/Build/Debug/spdlogd.dll

      # ${PROJECT_SOURCE_DIR}/Build/Debug/gladd.dll
      # ${PROJECT_SOURCE_DIR}/Build/Debug/glfw3d.dll
      # ${PROJECT_SOURCE_DIR}/Build/Debug/imguid.dll
      # ${PROJECT_SOURCE_DIR}/Build/Debug/glmd.dll
    )
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    # MPE RELEASE DLLS
    set(MPE_DLL_FILES
      ${PROJECT_SOURCE_DIR}/Build/Release/MPE.dll)
    set(DEPENENDENCY_DLL_FILES
      ${PROJECT_SOURCE_DIR}/Build/Release/fmt.dll
      ${PROJECT_SOURCE_DIR}/Build/Release/spdlog.dll

      # ${PROJECT_SOURCE_DIR}/Build/Release/glad.dll
      # ${PROJECT_SOURCE_DIR}/Build/Release/glfw3.dll
      # ${PROJECT_SOURCE_DIR}/Build/Release/imgui.dll
      # ${PROJECT_SOURCE_DIR}/Build/Release/glm.dll
    )
  endif()

  if(${VERBOSE})
    message("
-----------------------------------------------------------
MPE DLL FILES:\n")

    foreach(MPE_DLL ${MPE_DLL_FILES})
      message(STATUS "${MPE_DLL}")
    endforeach()

    message("
DEPENDENCY DLL FILES:\n")

    foreach(MPE_DEPENENDENCY_DLL ${DEPENENDENCY_DLL_FILES})
      message(STATUS "${MPE_DEPENENDENCY_DLL}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()
endif()

# INSTALLATION PROCEDURE FOR MPE
install(
  TARGETS MPE
  LIBRARY DESTINATION bin
  ARCHIVE DESTINATION bin
  RUNTIME DESTINATION bin)

# Copy the /MPE/Resources folder to Install/bin/Data
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/MPE/Resources/Shaders
  DESTINATION bin/Data
)

if(COMPILATION_PLATFORM STREQUAL "WIN32")
  add_custom_command(
    TARGET MPE
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${OpenCV_DLLs}
    $<TARGET_FILE_DIR:MPE>
    COMMENT "Copying OpenCV DLLs to MPE build..."
  )

  if(MPE_ANGLE)
    add_custom_command(
      TARGET MPE
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${ANGLE_DLLS}
      $<TARGET_FILE_DIR:MPE>
      COMMENT "Copying ANGLE DLLs to MPE build..."
    )
  endif(MPE_ANGLE)
endif()

# Copy the /MPE/Resources folder to /bin/Data
add_custom_command(
  TARGET MPE
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/MPE/Resources
  $<TARGET_FILE_DIR:MPE>/Data
  COMMENT "Copying MPE Resources DLLs to MPE build..."
)

if(${INSTALL_DLLS})
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  # EXAMPLES FOR FUTURE
  # install(FILES ${GTK_DLL_DEBUG_FILES} DESTINATION bin) install(FILES
  # ${MPE_DLL_DEBUG_FILES} DESTINATION bin)
  # install(FILES ${BOOST_PYTHON_DLL_DEBUG_FILES} DESTINATION bin)
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    # EXAMPLES FOR FUTURE
    # install(FILES ${GTK_DLL_RELEASE_FILES} DESTINATION bin) install(FILES
    # ${MPE_DLL_RELEASE_FILES} DESTINATION bin)
    # install(FILES ${BOOST_PYTHON_DLL_RELEASE_FILES} DESTINATION bin)
  endif()
endif()

# PUBLIC INCLUDES
set(MPE_PUBLIC_INCLUDES
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_SOURCE_DIR}/MPE"
)

if(${MAIN_TEST})
  add_subdirectory("${PROJECT_SOURCE_DIR}/Tests")
endif()

if(${EXAMPLES})
  add_subdirectory("${PROJECT_SOURCE_DIR}/Examples")
endif()

# TEMPORARY

# ADDING DUMMY EXECUTABLE
if(DUMMY_EXECUTABLE)
  add_executable(DUMMY "${PROJECT_SOURCE_DIR}/DUMMY/main.cpp")

  target_link_libraries(DUMMY
    PRIVATE MPE
  )
  target_include_directories(DUMMY PRIVATE ${MPE_PUBLIC_INCLUDES})

  # COMPILER DEFINITIONS FOR DUMMY
  target_compile_definitions(DUMMY PUBLIC ${MPE_PUBLIC_DEFINITIONS})

  if(${VERBOSE})
    get_target_property(DUMMY_DEFINITIONS_LIST DUMMY COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
DUMMY COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${DUMMY_DEFINITIONS_LIST})
      message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

  # INSTALLATION PROCEDURE
  install(
    TARGETS DUMMY
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin)

  install(FILES $<TARGET_RUNTIME_DLLS:DUMMY> DESTINATION bin)
endif(DUMMY_EXECUTABLE)

# TEMPORARY

# DOUBLE CHECKS IF THE SYSTEM IS RUNNING ON WINDOWS-X64 SYSTEM
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(STATUS "SIZE OF VOID POINTER: ${CMAKE_SIZEOF_VOID_P}")

  if(CROSS_COMPILATION)
    message(STATUS
      "\n-----------------------------------------------------------\n\tMPE DOES NOT OFFICIALLY SUPPORT NON X64 SYSTEMS.\n-----------------------------------------------------------")
  else()
    message(FATAL_ERROR "MPE SUPPORTS X64 SYSTEMS ONLY.")
    return()
  endif()
endif()

# TODO: Find a way to fix this issue without having to run a script or manually
# copying the dlls. install(SCRIPT
# "${CMAKE_CURRENT_SOURCE_DIR}/utils/core_copy_missing_dlls.cmake")

# ##############################################################################
# PROJECTS SANDBOX
if(${MPE_PROJECTS} AND ${MPE_PROJECT_SANDBOX})
  # ADD "SANDBOX" EXECUTABLE - THE ENTRYPOINT TO MPE
  add_executable(SANDBOX "${PROJECT_SOURCE_DIR}/Projects/Sandbox/Sandbox.cpp")

  target_link_libraries(SANDBOX PRIVATE
    MPE
  )
  target_include_directories(SANDBOX PRIVATE ${MPE_PUBLIC_INCLUDES})

  # COMPILER DEFINITIONS FOR SANDBOX
  target_compile_definitions(SANDBOX PUBLIC ${MPE_PUBLIC_DEFINITIONS})

  if(${VERBOSE})
    get_target_property(SANDBOX_DEFINITIONS_LIST SANDBOX COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
SANDBOX COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${SANDBOX_DEFINITIONS_LIST})
      message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

  # ADDING SANDBOX 2D LAYER
  file(GLOB_RECURSE SANDBOX2D_CPP
    "${PROJECT_SOURCE_DIR}/Projects/Sandbox/Sandbox2D/*.cpp")
  file(GLOB_RECURSE SANDBOX2D_H
    "${PROJECT_SOURCE_DIR}/Projects/Sandbox/Sandbox2D/*.h")
  add_library(SANDBOX2D STATIC ${SANDBOX2D_CPP})
  target_include_directories(SANDBOX2D PUBLIC
    ${SANDBOX2D_H}
    ${MPE_PUBLIC_INCLUDES}
  )

  target_link_libraries(SANDBOX2D PUBLIC MPE)

  # COMPILER DEFINITIONS FOR SANDBOX2D
  target_compile_definitions(SANDBOX2D PUBLIC ${MPE_PUBLIC_DEFINITIONS})

  if(${VERBOSE})
    get_target_property(SANDBOX2D_DEFINITIONS_LIST SANDBOX2D COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
SANDBOX2D COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${SANDBOX2D_DEFINITIONS_LIST})
      message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

  target_link_libraries(SANDBOX PUBLIC SANDBOX2D)

  # target_compile_features(SANDBOX PUBLIC ${CXX_VERSION_NAME})
  set_target_properties(SANDBOX PROPERTIES VERSION ${PROJECT_FULL_VERSION})
  set_target_properties(SANDBOX PROPERTIES OUTPUT_NAME "MPE-SANDBOX")

  # Copy the /Project/*/Data folder to the build directory
  add_custom_command(
    TARGET SANDBOX
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Projects/Sandbox/Data
    $<TARGET_FILE_DIR:SANDBOX>/Data
  )

  # Copy the /Project/*/Data folder to the install directory
  install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/Projects/Sandbox/Data
    DESTINATION bin
  )

  # INSTALLATION PROCEDURE
  install(
    TARGETS SANDBOX
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin)

  install(FILES $<TARGET_RUNTIME_DLLS:SANDBOX> DESTINATION bin)

  if(${VERBOSE})
    message(STATUS "MPE-SANDBOX ADDED.")
  endif()
endif(${MPE_PROJECTS} AND ${MPE_PROJECT_SANDBOX})

# ##############################################################################
if(${MPE_PROJECTS} AND ${MPE_PROJECT_PROJECTPICKER})
  # ADD "ProjectPicker" EXECUTABLE - THE ENTRYPOINT TO MPE
  add_executable(ProjectPicker "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/ProjectPicker.cpp")

  target_link_libraries(ProjectPicker PRIVATE
    MPE
  )
  target_include_directories(ProjectPicker PRIVATE ${MPE_PUBLIC_INCLUDES})

  # COMPILER DEFINITIONS FOR ProjectPicker
  target_compile_definitions(ProjectPicker PUBLIC ${MPE_PUBLIC_DEFINITIONS})

  if(${VERBOSE})
    get_target_property(ProjectPicker_DEFINITIONS_LIST ProjectPicker COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
ProjectPicker COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${ProjectPicker_DEFINITIONS_LIST})
      message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

  # ADDING TEST LAYERS
  file(GLOB_RECURSE TEST_LAYERS_CPP
    "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/*.cpp")
  file(GLOB_RECURSE TEST_LAYERS_H
    "${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Tests/*.h")
  add_library(TEST_LAYERS STATIC ${TEST_LAYERS_CPP})
  target_include_directories(TEST_LAYERS PUBLIC
    ${TEST_LAYERS_H}
    ${MPE_PUBLIC_INCLUDES}
  )

  target_link_libraries(TEST_LAYERS PUBLIC MPE)

  # COMPILER DEFINITIONS FOR TEST_LAYERS
  target_compile_definitions(TEST_LAYERS PUBLIC ${MPE_PUBLIC_DEFINITIONS})

  if(${VERBOSE})
    get_target_property(TEST_LAYERS_DEFINITIONS_LIST TEST_LAYERS COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
TEST_LAYERS COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${TEST_LAYERS_DEFINITIONS_LIST})
      message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

  target_link_libraries(ProjectPicker PUBLIC TEST_LAYERS)

  # target_compile_features(SANDBOX PUBLIC ${CXX_VERSION_NAME})
  set_target_properties(ProjectPicker PROPERTIES VERSION ${PROJECT_FULL_VERSION})
  set_target_properties(ProjectPicker PROPERTIES OUTPUT_NAME "MPE-ProjectPicker")

  # Copy the /Project/*/Data folder to the build directory
  add_custom_command(
    TARGET ProjectPicker
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Data
    $<TARGET_FILE_DIR:ProjectPicker>/Data
  )

  # Copy the /Project/*/Data folder to the install directory
  install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/Data
    DESTINATION bin
  )

  # INSTALLATION PROCEDURE
  install(
    TARGETS ProjectPicker
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin)

  install(FILES $<TARGET_RUNTIME_DLLS:ProjectPicker> DESTINATION bin)

  if(${VERBOSE})
    message(STATUS "MPE-ProjectPicker ADDED.")
  endif()
endif(${MPE_PROJECTS} AND ${MPE_PROJECT_PROJECTPICKER})

# ##############################################################################
# TESTS add_executable(TEST "${PROJECT_SOURCE_DIR}/Tests/Unit.cpp")

# file(GLOB_RECURSE TEST_CPP "${PROJECT_SOURCE_DIR}/Tests/*.cpp"
# #"${PROJECT_SOURCE_DIR}/Tests/Primitive/*.cpp" )

# file(GLOB_RECURSE TEST_H "${PROJECT_SOURCE_DIR}/Tests/*.h"
# #"${PROJECT_SOURCE_DIR}/Tests/Primitive/*.h" )

# # add_library(TEST_SRC STATIC ${TEST_CPP}) #
# target_include_directories(TEST_SRC PUBLIC ${TEST_H}) #
# target_link_libraries(TEST_SRC PUBLIC MPE) # target_link_libraries(TEST PUBLIC
# MPE) # target_link_libraries(TEST PUBLIC TEST_SRC)

# target_link_libraries(TEST PUBLIC MPE) target_include_directories(TEST PUBLIC
# ${TEST_CPP} ${TEST_H})

# ##############################################################################
# PROJECTS PONG
if(${MPE_PROJECTS} AND ${MPE_PROJECT_PONG})
  add_executable(PONG
    "${PROJECT_SOURCE_DIR}/Projects/Pong/ProjectSelector.cpp")

  target_include_directories(PONG PRIVATE ${MPE_PUBLIC_INCLUDES})

  file(GLOB_RECURSE PONG_CPP
    "${PROJECT_SOURCE_DIR}/Projects/Pong/*.cpp"
    "${PROJECT_SOURCE_DIR}/Projects/Pong/Core/*.cpp")

  file(GLOB_RECURSE PONG_H
    "${PROJECT_SOURCE_DIR}/Projects/Pong/*.h"
    "${PROJECT_SOURCE_DIR}/Projects/Pong/Core/*.h")

  add_library(PONG_SRC STATIC ${PONG_CPP})
  target_include_directories(PONG_SRC PUBLIC
    ${PONG_H}
    ${MPE_PUBLIC_INCLUDES}
  )

  # COMPILER DEFINITIONS FOR PONG_SRC
  target_compile_definitions(PONG_SRC PUBLIC ${MPE_PUBLIC_DEFINITIONS})

  if(${VERBOSE})
    get_target_property(PONG_SRC_DEFINITIONS_LIST PONG_SRC COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
PONG_SRC COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${PONG_SRC_DEFINITIONS_LIST})
      message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

  target_link_libraries(PONG_SRC PUBLIC MPE)
  target_link_libraries(PONG PUBLIC MPE)
  target_link_libraries(PONG PUBLIC PONG_SRC)

  set_target_properties(PONG PROPERTIES VERSION ${PROJECT_FULL_VERSION})
  set_target_properties(PONG PROPERTIES OUTPUT_NAME "MPE-PONG")

  # COMPILER DEFINITIONS FOR PONG
  target_compile_definitions(PONG PUBLIC ${MPE_PUBLIC_DEFINITIONS})

  if(${VERBOSE})
    get_target_property(PONG_DEFINITIONS_LIST PONG COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
PONG COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${PONG_DEFINITIONS_LIST})
      message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

  # Copy the /Project/*/Data folder to the build directory
  add_custom_command(
    TARGET PONG
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Projects/Pong/Data
    $<TARGET_FILE_DIR:PONG>/Data
  )

  # Copy the /Project/*/Data folder to the install directory
  install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/Projects/Pong/Data
    DESTINATION bin
  )

  # INSTALLATION PROCEDURE
  install(
    TARGETS PONG
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin)

  install(FILES $<TARGET_RUNTIME_DLLS:PONG> DESTINATION bin)

  if(${VERBOSE})
    message(STATUS "MPE-PONG ADDED.")
  endif()
endif(${MPE_PROJECTS} AND ${MPE_PROJECT_PONG})

# ##############################################################################

# ADDING OPENCV_TEST EXECUTABLE
if(${MPE_PROJECTS} AND ${MPE_PROJECT_OPENCVTEST})
  add_executable(OPENCV_TEST "${PROJECT_SOURCE_DIR}/Projects/OpenCVTest/OpenCVTest.cpp")

  target_link_libraries(OPENCV_TEST PRIVATE
    MPE
    ${OpenCV_LIBS}
  )

  target_include_directories(OPENCV_TEST PRIVATE
    ${MPE_PUBLIC_INCLUDES}
    ${OpenCV_LIBS}
  )

  # COMPILER DEFINITIONS FOR OPENCV_TEST
  target_compile_definitions(OPENCV_TEST PUBLIC ${MPE_PUBLIC_DEFINITIONS})

  if(${VERBOSE})
    get_target_property(OPENCV_TEST_DEFINITIONS_LIST OPENCV_TEST COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
OPENCV_TEST COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${OPENCV_TEST_DEFINITIONS_LIST})
      message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
  endif()

  # Copy the /Project/*/Data folder to the build directory
  add_custom_command(
    TARGET OPENCV_TEST
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Projects/OpenCVTest/Data
    $<TARGET_FILE_DIR:OPENCV_TEST>/Data
  )

  # Copy the /Project/*/Data folder to the install directory
  install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/Projects/OpenCVTest/Data
    DESTINATION bin
  )

  # INSTALLATION PROCEDURE
  install(
    TARGETS OPENCV_TEST
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin)

  install(FILES $<TARGET_RUNTIME_DLLS:OPENCV_TEST> DESTINATION bin)
endif(${MPE_PROJECTS} AND ${MPE_PROJECT_OPENCVTEST})

# ##############################################################################

# CHECK IF SYSTEMS IS RUNNING WINDOWS AND ADD NECESSARY ATTRIBUTES EVEN THOUGH
# CURRENTLY ONLY WINDOWS IS SUPPORTED, ADDING THIS CHECK WILL MAKE IT EASIER TO
# ADD SUPPORT FOR OTHER SYSTEMS IN THE FUTURE
if(COMPILATION_PLATFORM STREQUAL "WIN32")
  # TOGGLE WIN CMD RESOURCE COPY SCRIPT
  set(CMD_RES_CPY OFF)

  if(CMD_RES_CPY)
    # ADDING A SCRIPT THAT MIRROS THE FOLDER IN source/Sandbox/Data to build/Data
    add_custom_command(
      TARGET SANDBOX
      POST_BUILD
      COMMAND ${PROJECT_SOURCE_DIR}/utility/scripts/windows/CPBMDTB.bat)

    # THIS MIGHT THROW SOME ERRORS IN CMAKE, BUT IF BUILT AGAIN SHOULD WORK FINE
    add_custom_target(
      DATASCRIPT
      COMMAND ${PROJECT_SOURCE_DIR}/utility/scripts/windows/CPBMDTB.bat)

    add_dependencies(SANDBOX DATASCRIPT)
  endif(CMD_RES_CPY)
endif(COMPILATION_PLATFORM STREQUAL "WIN32")

if(COMPILATION_PLATFORM STREQUAL "UNIX")
endif(COMPILATION_PLATFORM STREQUAL "UNIX")

if(COMPILATION_PLATFORM STREQUAL "OSX")
endif(COMPILATION_PLATFORM STREQUAL "OSX")

message(STATUS "MPE/CMAKE SUCCESSFULLY FINISHED.")