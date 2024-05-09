add_executable(MPE-Core-Logging-Log "LogTest.cpp")

set_target_properties(MPE-Core-Logging-Log PROPERTIES OUTPUT_NAME "MPE-Core-Logging-Log")
target_link_libraries(MPE-Core-Logging-Log PRIVATE
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
    MPE
)
target_include_directories(MPE-Core-Logging-Log PRIVATE ${MPE_PUBLIC_INCLUDES})

add_test(MPE-Core-Logging-Log MPE-Core-Logging-Log)

install(TARGETS MPE-Core-Logging-Log
    RUNTIME DESTINATION Tests/MPE/Core/Logging
    LIBRARY DESTINATION Tests/MPE/Core/Logging
    ARCHIVE DESTINATION Tests/MPE/Core/Logging)
install(FILES $<TARGET_RUNTIME_DLLS:MPE-Core-Logging-Log> DESTINATION Tests/MPE/Core/Logging)

# TODO: Potential optimization for the future if CI is used to run these test: Do not copy the .dlls; instead add the core MPE build path to the PATH environment variable
add_custom_command(TARGET MPE-Core-Logging-Log POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${MPE_DLL_FILES}"
    "$<TARGET_FILE_DIR:MPE-Core-Logging-Log>"
    COMMENT "Copying MPE.dll to executable directory..."
)

# TODO: At the moment .dlls are not copied to the test directory. The workaround is to: 1. Copy the .dlls to the test directory manually. 2. Copy the .dlls with a post_install process. 3. Add the built library to the path
if(${VERBOSE})
    message(STATUS "Log CONFIGURATION TEST ADDED.")
endif()

if(${VERBOSE})
    message(STATUS "Logging-Log TEST ADDED.")
endif()