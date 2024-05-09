add_executable(MPE-Core-Time "TimeTest.cpp")

set_target_properties(MPE-Core-Time PROPERTIES OUTPUT_NAME "MPE-Core-Time")
target_link_libraries(MPE-Core-Time PRIVATE
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
    MPE
)
target_include_directories(MPE-Core-Time PRIVATE ${MPE_PUBLIC_INCLUDES})

add_test(MPE-Core-Time MPE-Core-Time)

install(TARGETS MPE-Core-Time
    RUNTIME DESTINATION Tests/MPE/Core/Time
    LIBRARY DESTINATION Tests/MPE/Core/Time
    ARCHIVE DESTINATION Tests/MPE/Core/Time)
install(FILES $<TARGET_RUNTIME_DLLS:MPE-Core-Time> DESTINATION Tests/MPE/Core/Time)

# TODO: Potential optimization for the future if CI is used to run these test: Do not copy the .dlls; instead add the core MPE build path to the PATH environment variable
add_custom_command(TARGET MPE-Core-Time PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${MPE_DLL_FILES}"
    "$<TARGET_FILE_DIR:MPE-Core-Time>"
    COMMENT "Copying MPE.dll to executable directory..."
)

foreach(dll ${DEPENDENCY_DLL_FILES})
    add_custom_command(TARGET MPE-Core-Time PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${dll}
        $<TARGET_FILE_DIR:MPE-Core-Time>
        COMMENT "Copying ${dll} to executable directory..."
    )
endforeach()

# TODO: At the moment .dlls are not copied to the test directory. The workaround is to: 1. Copy the .dlls to the test directory manually. 2. Copy the .dlls with a post_install process. 3. Add the built library to the path
if(${VERBOSE})
    message(STATUS "Time CONFIGURATION TEST ADDED.")
endif()

if(${VERBOSE})
    message(STATUS "Time TEST ADDED.")
endif()