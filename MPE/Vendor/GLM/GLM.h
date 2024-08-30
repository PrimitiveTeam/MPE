#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#ifdef MPE_OPENGLES
#    define GLM_FORCE_CTOR_INIT
#    define GLM_FORCE_PURE
#endif
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#if !defined(MPE_PLATFORM_OSX)
#    include <glm/ext.hpp>
#endif

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_clip_space.hpp>