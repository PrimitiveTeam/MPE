find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_library(COCOA_LIBRARY Cocoa)

if(${VERBOSE})
    message("
***********************************************************
  * fmt
  * spdlog
  * glfw3
  * glm
  * Freetype
  * COCOA
***********************************************************")
endif()