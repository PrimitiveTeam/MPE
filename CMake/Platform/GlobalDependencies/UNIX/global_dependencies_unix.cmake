find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenAL CONFIG REQUIRED)

if(MPE_USE_X11)
  find_package(X11 REQUIRED)
endif()

if(MPE_USE_WAYLAND)
  find_package(Wayland REQUIRED)
endif()

if(MPE_USE_X11)
  if(${VERBOSE})
    message("
***********************************************************
  * fmt
  * spdlog
  * glfw3
  * glm
  * Freetype
  * OpenAL
  * X11
***********************************************************")
  endif()
elseif(MPE_USE_WAYLAND)
  if(${VERBOSE})
    message("
***********************************************************
  * fmt
  * spdlog
  * glfw3
  * glm
  * Freetype
  * OpenAL
  * Wayland
***********************************************************")
  endif()
else()
  if(${VERBOSE})
    message("
***********************************************************
  * fmt
  * spdlog
  * glfw3
  * glm
  * Freetype
  * OpenAL
***********************************************************")
  endif()
endif()