if(${MPE_LIBRARY_TYPE} STREQUAL STATIC)
    add_library(MPE STATIC
        ${MPE_CPP}
        ${MPE_WIN32_CPP}
    )
    target_compile_definitions(MPE PRIVATE MPE_STATIC_LIBRARY)

elseif(${MPE_LIBRARY_TYPE} STREQUAL SHARED)
    add_library(MPE SHARED
        ${MPE_CPP}
        ${MPE_WIN32_CPP}
    )

    target_compile_definitions(MPE PUBLIC MPE_DYNAMIC_LIBRARY)
    target_compile_definitions(MPE PRIVATE MPE_BUILD_DLL)
else()
    message(FATAL_ERROR "LIBRARY TYPE {${MPE_LIBRARY_TYPE}} NOT SUPPORTED.")
endif()

target_compile_definitions(MPE PUBLIC MPE_PLATFORM_WINDOWS)
target_compile_definitions(MPE PUBLIC MPE_ENABLE_ASSERTS)
target_compile_definitions(MPE PUBLIC MPE_COMPILER_${CURRENT_COMPILER})

# ENABLE PROFILING FOR DEBUG BUILS
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(MPE PUBLIC MPE_CORE_DEBUG_PROFILING)
    target_compile_definitions(MPE PUBLIC MPE_DEBUG_PROFILING)
    target_compile_definitions(MPE PUBLIC MPE_ENABLE_DEBUG_LOG)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)

# GRAPHICS APIS
if(MPE_OPENGL)
    target_compile_definitions(MPE PUBLIC MPE_OPENGL)
endif()

if(MPE_OPENGLES)
    target_compile_definitions(MPE PUBLIC MPE_OPENGLES)
endif()

target_compile_definitions(MPE PUBLIC MPE_FULL_VERSION_${PROJECT_FULL_VERSION})

# CMAKE IS NOT INHERETING COMPILER FLAGS PROPERLY
set(MPE_PUBLIC_DEFINITIONS)

if(MPE_LIBRARY_TYPE STREQUAL SHARED)
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_DYNAMIC_LIBRARY)
else()
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_STATIC_LIBRARY)
endif()

list(APPEND MPE_PUBLIC_DEFINITIONS MPE_PLATFORM_WINDOWS)
list(APPEND MPE_PUBLIC_DEFINITIONS MPE_ENABLE_ASSERTS)
list(APPEND MPE_PUBLIC_DEFINITIONS MPE_COMPILER_${CURRENT_COMPILER})

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_CORE_DEBUG_PROFILING MPE_DEBUG_PROFILING MPE_ENABLE_DEBUG_LOG)
endif()

# GRAPHICS APIS
if(MPE_OPENGL)
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_OPENGL)
endif()

if(MPE_OPENGLES)
    list(APPEND MPE_PUBLIC_DEFINITIONS MPE_OPENGLES)
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