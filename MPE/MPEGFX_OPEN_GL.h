#pragma once

// This will be used to include all core headers for specific platforms.

// Need this for euler/quaternion conversions
#define GLM_ENABLE_EXPERIMENTAL

// ----- OPEN GL -----
#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/OpenGL/OpenGLSettings.h"
#include "Platform/OpenGL/Pipeline/OpenGLVertexBuffer.h"
#include "Platform/OpenGL/Pipeline/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/Pipeline/OpenGLVertexArray.h"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"
#include "Platform/OpenGL/Text/OpenGLTextRenderer.h"
#include "Platform/OpenGL/Textures/OpenGLTexture.h"
#include "Platform/OpenGL/Textures/OpenGLTexture2D.h"
#include "Platform/OpenGL/Textures/OpenGLTextTexture.h"
#include "Platform/OpenGL/Utilities/OpenGLUtilities.h"
// ----- OPEN GL -----