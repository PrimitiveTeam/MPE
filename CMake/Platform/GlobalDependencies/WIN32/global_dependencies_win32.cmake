find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)
# find_package(freetype-gl CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)

if(${VERBOSE})
    message("
***********************************************************
  * fmt
  * spdlog
  * glfw3
  * glm
  * freetype
  * OpenAL
***********************************************************")
endif()