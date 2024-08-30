add_executable(Editor
    "${PROJECT_SOURCE_DIR}/Editor/Editor.cpp"
    "${PROJECT_SOURCE_DIR}/Editor/EditorSource.cpp"
)

target_link_libraries(Editor PRIVATE
    MPE
    MPE_EDITOR
)
target_include_directories(
    Editor
    PRIVATE ${MPE_PUBLIC_INCLUDES}
    PRIVATE ${MPE_EDITOR_PUBLIC_INCLUDES}
)

# COMPILER DEFINITIONS FOR Editor
target_compile_definitions(Editor PUBLIC ${MPE_PUBLIC_DEFINITIONS})

if(${VERBOSE})
    get_target_property(EDITOR_DEFINITIONS_LIST Editor COMPILE_DEFINITIONS)

    message("
-----------------------------------------------------------
EDITOR EXE COMPILE DEFINITIONS:\n")

    foreach(DEFINITION ${EDITOR_DEFINITIONS_LIST})
        message(STATUS "${DEFINITION}")
    endforeach()

    message("
-----------------------------------------------------------")
endif()

set_target_properties(Editor PROPERTIES VERSION ${PROJECT_FULL_VERSION})
set_target_properties(Editor PROPERTIES OUTPUT_NAME "Editor")

# Copy the /Editor/Data folder to the build directory
add_custom_command(
    TARGET Editor
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Editor/Data
    $<TARGET_FILE_DIR:Editor>/Data
)

# Copy the /Editor/Data folder to the install directory
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/Editor/Data
    DESTINATION bin
)

# INSTALLATION PROCEDURE
install(
    TARGETS Editor
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin)

install(FILES $<TARGET_RUNTIME_DLLS:Editor> DESTINATION bin)

if(${VERBOSE})
    message(STATUS "MPE-Editor EXE ADDED.")
endif()