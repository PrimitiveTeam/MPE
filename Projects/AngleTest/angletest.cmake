if(COMPILATION_PLATFORM STREQUAL "OSX")
    add_executable(AngleEGLTest "${PROJECT_SOURCE_DIR}/Projects/AngleTest/eglTest.mm")

    target_link_libraries(AngleEGLTest
        PRIVATE MPE
    )

    # COMPILER DEFINITIONS FOR AngleEGLTest
    target_compile_definitions(AngleEGLTest PUBLIC ${MPE_PUBLIC_DEFINITIONS})
    get_target_property(AngleEGLTest_DEFINITIONS_LIST AngleEGLTest COMPILE_DEFINITIONS)

    # INSTALLATION PROCEDURE
    install(
        TARGETS AngleEGLTest
        LIBRARY DESTINATION bin
        ARCHIVE DESTINATION bin
        RUNTIME DESTINATION bin)

    install(FILES $<TARGET_RUNTIME_DLLS:AngleEGLTest> DESTINATION bin)

    modify_dylib_paths(AngleEGLTest)

    add_executable(AngleGLES2Test "${PROJECT_SOURCE_DIR}/Projects/AngleTest/gles2.mm")

    target_link_libraries(AngleGLES2Test
        PRIVATE MPE
    )

    # COMPILER DEFINITIONS FOR AngleGLES2Test
    target_compile_definitions(AngleGLES2Test PUBLIC ${MPE_PUBLIC_DEFINITIONS})
    get_target_property(AngleGLES2Test_DEFINITIONS_LIST AngleGLES2Test COMPILE_DEFINITIONS)

    # INSTALLATION PROCEDURE
    install(
        TARGETS AngleGLES2Test
        LIBRARY DESTINATION bin
        ARCHIVE DESTINATION bin
        RUNTIME DESTINATION bin)

    install(FILES $<TARGET_RUNTIME_DLLS:AngleGLES2Test> DESTINATION bin)

    modify_dylib_paths(AngleGLES2Test)

    add_executable(AngleGLES3Test "${PROJECT_SOURCE_DIR}/Projects/AngleTest/gles3.mm")

    target_link_libraries(AngleGLES3Test
        PRIVATE MPE
    )

    # COMPILER DEFINITIONS FOR AngleGLES3Test
    target_compile_definitions(AngleGLES3Test PUBLIC ${MPE_PUBLIC_DEFINITIONS})
    get_target_property(AngleGLES3Test_DEFINITIONS_LIST AngleGLES3Test COMPILE_DEFINITIONS)

    # INSTALLATION PROCEDURE
    install(
        TARGETS AngleGLES3Test
        LIBRARY DESTINATION bin
        ARCHIVE DESTINATION bin
        RUNTIME DESTINATION bin)

    install(FILES $<TARGET_RUNTIME_DLLS:AngleGLES3Test> DESTINATION bin)

    modify_dylib_paths(AngleGLES3Test)
else()
    add_executable(AngleEGLTest "${PROJECT_SOURCE_DIR}/Projects/AngleTest/eglTest.cpp")

    target_link_libraries(AngleEGLTest
        PRIVATE MPE
    )

    # COMPILER DEFINITIONS FOR AngleEGLTest
    target_compile_definitions(AngleEGLTest PUBLIC ${MPE_PUBLIC_DEFINITIONS})
    get_target_property(AngleEGLTest_DEFINITIONS_LIST AngleEGLTest COMPILE_DEFINITIONS)

    # INSTALLATION PROCEDURE
    install(
        TARGETS AngleEGLTest
        LIBRARY DESTINATION bin
        ARCHIVE DESTINATION bin
        RUNTIME DESTINATION bin)

    install(FILES $<TARGET_RUNTIME_DLLS:AngleEGLTest> DESTINATION bin)

    add_executable(AngleGLES2Test "${PROJECT_SOURCE_DIR}/Projects/AngleTest/gles2.cpp")

    target_link_libraries(AngleGLES2Test
        PRIVATE MPE
    )

    # COMPILER DEFINITIONS FOR AngleGLES2Test
    target_compile_definitions(AngleGLES2Test PUBLIC ${MPE_PUBLIC_DEFINITIONS})
    get_target_property(AngleGLES2Test_DEFINITIONS_LIST AngleGLES2Test COMPILE_DEFINITIONS)

    # INSTALLATION PROCEDURE
    install(
        TARGETS AngleGLES2Test
        LIBRARY DESTINATION bin
        ARCHIVE DESTINATION bin
        RUNTIME DESTINATION bin)

    install(FILES $<TARGET_RUNTIME_DLLS:AngleGLES2Test> DESTINATION bin)

    add_executable(AngleGLES3Test "${PROJECT_SOURCE_DIR}/Projects/AngleTest/gles3.cpp")

    target_link_libraries(AngleGLES3Test
        PRIVATE MPE
    )

    # COMPILER DEFINITIONS FOR AngleGLES3Test
    target_compile_definitions(AngleGLES3Test PUBLIC ${MPE_PUBLIC_DEFINITIONS})
    get_target_property(AngleGLES3Test_DEFINITIONS_LIST AngleGLES3Test COMPILE_DEFINITIONS)

    # INSTALLATION PROCEDURE
    install(
        TARGETS AngleGLES3Test
        LIBRARY DESTINATION bin
        ARCHIVE DESTINATION bin
        RUNTIME DESTINATION bin)

    install(FILES $<TARGET_RUNTIME_DLLS:AngleGLES3Test> DESTINATION bin)
endif()