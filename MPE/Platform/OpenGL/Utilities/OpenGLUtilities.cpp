#include "OpenGLUtilities.h"
#include "MPEPCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MPE
{
void OpenGLUtilities::ToggleGlPolygonMode()
{
    m_GlPolygonMode = !m_GlPolygonMode;
    if (m_GlPolygonMode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
}