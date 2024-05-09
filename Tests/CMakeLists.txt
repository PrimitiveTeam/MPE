find_package(GTest CONFIG REQUIRED)

add_subdirectory("MPE")

if(${VERBOSE})
    message(STATUS "MPE GTEST SUITE ADDED.")
endif()