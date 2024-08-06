add_executable(DUMMY "${PROJECT_SOURCE_DIR}/Projects/DUMMY/main.cpp")

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

if(COMPILATION_PLATFORM STREQUAL "OSX" AND MPE_ANGLE)
    # set_target_properties(DUMMY PROPERTIES INSTALL_RPATH "@executable_path/")
    # message(STATUS "Setting RPATH for DUMMY target to @executable_path/")
    modify_dylib_paths(DUMMY)
endif(COMPILATION_PLATFORM STREQUAL "OSX" AND MPE_ANGLE)
