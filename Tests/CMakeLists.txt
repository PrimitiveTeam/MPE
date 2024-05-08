set(gtest_DIR "${VCPKG_ROOT_PATH}\\installed\\x64-windows\\share\\gtest")
find_package(GTest CONFIG REQUIRED)

add_subdirectory("MPE")

if(${VERBOSE})
    message(STATUS "MPE GTEST SUITE ADDED.")
endif()