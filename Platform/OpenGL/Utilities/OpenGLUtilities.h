#pragma once

#include "MPE/Core/_CORE.h"

namespace MPE
{
class MPE_API OpenGLUtilities
{
  public:
    static OpenGLUtilities& getInstance()
    {
        static OpenGLUtilities instance;
        return instance;
    }

    OpenGLUtilities(const OpenGLUtilities&) = delete;
    OpenGLUtilities& operator=(const OpenGLUtilities&) = delete;

    bool GetGlPolygonMode() const { return m_GlPolygonMode; }
    void ToggleGlPolygonMode();

  private:
    OpenGLUtilities() = default;
    ~OpenGLUtilities() = default;

    bool m_GlPolygonMode = false;
};
}