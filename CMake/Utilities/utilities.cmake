if(COMPILATION_PLATFORM STREQUAL "WIN32")
elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
elseif(COMPILATION_PLATFORM STREQUAL "OSX")
    if(MPE_ANGLE)
        include("${PROJECT_SOURCE_DIR}/CMake/Utilities/Platform/OSX/angle_dylib_correct_link.cmake")
    endif(MPE_ANGLE)
elseif(COMPILATION_PLATFORM STREQUAL "RPI4")
else()
    message(FATAL_ERROR "${COMPILATION_PLATFORM} NOT SUPPORTED.")
endif()