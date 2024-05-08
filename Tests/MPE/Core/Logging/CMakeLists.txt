add_executable(MPE-Core-Logging-Log "LogTest.cpp")

set_target_properties(MPE-Core-Logging-Log PROPERTIES OUTPUT_NAME "MPE-Core-Logging-Log")
target_link_libraries(MPE-Core-Logging-Log PRIVATE
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
    MPE_DLL_FILES
)

add_test(MPE-Core-Logging-Log MPE-Core-Logging-Log)

install(TARGETS MPE-Core-Logging-Log
    RUNTIME DESTINATION Tests/MPE/Core/Logging
    LIBRARY DESTINATION Tests/MPE/Core/Logging
    ARCHIVE DESTINATION Tests/MPE/Core/Logging)
install(FILES $<TARGET_RUNTIME_DLLS:MPE-Core-Logging-Log> DESTINATION Tests/MPE/Core/Logging)
install(FILES ${MPE_DLL_FILES} DESTINATION Tests/MPE/Core/Logging)

# TODO: At the moment .dlls are not copied to the test directory. The workaround is to: 1. Copy the .dlls to the test directory manually. 2. Copy the .dlls with a post_install process. 3. Add the built library to the path
if(${VERBOSE})
    message(STATUS "Log CONFIGURATION TEST ADDED.")
endif()

if(${VERBOSE})
    message(STATUS "Logging-Log TEST ADDED.")
endif()