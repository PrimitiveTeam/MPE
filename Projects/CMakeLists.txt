# DUMMY
if(MPE_PROJECT_DUMMY)
    add_subdirectory("${PROJECT_SOURCE_DIR}/Projects/DUMMY")
endif(MPE_PROJECT_DUMMY)

# SANDBOX
if(MPE_PROJECT_SANDBOX)
    add_subdirectory("${PROJECT_SOURCE_DIR}/Projects/Sandbox")
endif(MPE_PROJECT_SANDBOX)

# PROJECT PICKER
if(MPE_PROJECT_PROJECTPICKER)
    add_subdirectory("${PROJECT_SOURCE_DIR}/Projects/ProjectPicker")
endif(MPE_PROJECT_PROJECTPICKER)

# PONG
if(MPE_PROJECT_PONG)
    add_subdirectory("${PROJECT_SOURCE_DIR}/Projects/Pong")
endif(MPE_PROJECT_PONG)

# OPENCV TEST
if(MPE_PROJECT_OPENCVTEST)
    add_subdirectory("${PROJECT_SOURCE_DIR}/Projects/OpenCVTest")
endif(MPE_PROJECT_OPENCVTEST)