# S1 - STAGE ONE - STATIC VS SHARED LIBRARY
# BUILD MPE LIBRARY BASED ON SET LIBRARY TYPE

if(COMPILATION_PLATFORM STREQUAL "WIN32")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/WIN32/S1/build_win32_s1.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/UNIX/S1/build_unix_s1.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "OSX")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/OSX/S1/build_osx_s1.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/RPI4/S1/build_rpi4_s1.cmake")
else()
    message(FATAL_ERROR "${COMPILATION_PLATFORM} NOT SUPPORTED.")
endif()

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

# S2 - STAGE TWO - LINKING LIBRARIES AND INCLUDING DIRECTORIES
if(COMPILATION_PLATFORM STREQUAL "WIN32")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/WIN32/S2/build_win32_s2.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/UNIX/S2/build_unix_s2.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "OSX")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/OSX/S2/build_osx_s2.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/RPI4/S2/build_rpi4_s2.cmake")
else()
    message(FATAL_ERROR "${COMPILATION_PLATFORM} NOT SUPPORTED.")
endif()

# S3 - STAGE THREE - INSTALL PROPERTIES
if(COMPILATION_PLATFORM STREQUAL "WIN32")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/WIN32/S3/build_win32_s3.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/UNIX/S3/build_unix_s3.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "OSX")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/OSX/S3/build_osx_s3.cmake")
elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
    include("${PROJECT_SOURCE_DIR}/CMake/Platform/Build/Editor/RPI4/S3/build_rpi4_s3.cmake")
else()
    message(FATAL_ERROR "${COMPILATION_PLATFORM} NOT SUPPORTED.")
endif()