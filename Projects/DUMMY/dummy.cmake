
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
