find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

if(${VERBOSE})
    message("
***********************************************************
  * fmt
  * spdlog
  * glfw3
  * glm
***********************************************************")
endif()