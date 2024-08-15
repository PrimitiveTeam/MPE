# DUMMY
if(MPE_PROJECT_DUMMY)
    include("${PROJECT_SOURCE_DIR}/Projects/DUMMY/dummy.cmake")
endif(MPE_PROJECT_DUMMY)

# SANDBOX
if(MPE_PROJECT_SANDBOX)
    include("${PROJECT_SOURCE_DIR}/Projects/Sandbox/sandbox.cmake")
endif(MPE_PROJECT_SANDBOX)

# PROJECT PICKER
if(MPE_PROJECT_PROJECTPICKER)
    include("${PROJECT_SOURCE_DIR}/Projects/ProjectPicker/projectpicker.cmake")
endif(MPE_PROJECT_PROJECTPICKER)

# PONG
if(MPE_PROJECT_PONG)
    include("${PROJECT_SOURCE_DIR}/Projects/Pong/pong.cmake")
endif(MPE_PROJECT_PONG)

# OPENCV TEST
if(MPE_PROJECT_OPENCVTEST)
    include("${PROJECT_SOURCE_DIR}/Projects/OpenCVTest/opencvtest.cmake")
endif(MPE_PROJECT_OPENCVTEST)

# ANGLE TEST
if(MPE_PROJECT_ANGLETEST)
    include("${PROJECT_SOURCE_DIR}/Projects/AngleTest/angletest.cmake")
endif(MPE_PROJECT_ANGLETEST)

# FREETYPE TEST
if(MPE_PROJECT_FREETYPE)
    include("${PROJECT_SOURCE_DIR}/Projects/FreeType/freetype.cmake")
endif(MPE_PROJECT_FREETYPE)

# OPENAL TEST
if(MPE_PROJECT_OPENAL)
    include("${PROJECT_SOURCE_DIR}/Projects/OpenAL/openal.cmake")
endif(MPE_PROJECT_OPENAL)