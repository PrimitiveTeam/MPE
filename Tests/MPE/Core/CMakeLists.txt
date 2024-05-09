add_subdirectory("Logging")

if(${VERBOSE})
    message(STATUS "Logging GTEST SUBMODULE ADDED.")
endif()

add_subdirectory("Time")

if(${VERBOSE})
    message(STATUS "Time GTEST SUBMODULE ADDED.")
endif()