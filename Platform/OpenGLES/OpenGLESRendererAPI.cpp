#include "OpenGLESRendererAPI.h"
#include "MPE/MPEPCH.h"

#include "Platform/OpenGLES/Utilities/OpenGLESUtilities.h"

#include <GLES3/gl31.h>

namespace MPE
{
void OpenGLESRendererAPI::Init()
{
    m_settings = new OpenGLESSettings();

    // std::string OpenGL_INFO = "\nOpenGL Info:\n";

    auto graphicalContextProps = m_settings->GetGraphicalContextProps();
    int openGLVersionMajor;
    int openGLVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &openGLVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &openGLVersionMinor);

    // OpenGL_INFO += "\tOpenGL Version: " + std::to_string(openGLVersionMajor) + "." + std::to_string(openGLVersionMinor) + "\n";
    graphicalContextProps->majorVersion = openGLVersionMajor;
    graphicalContextProps->minorVersion = openGLVersionMinor;

#ifdef MPE_PLATFORM_WINDOWS
    MPE_CORE_ASSERT(openGLVersionMajor > 3 || (openGLVersionMajor == 3 && openGLVersionMinor >= 1), "MPE REQUIRES OPENGLES VERSION 3.1 OR GREATER.");
#elif MPE_PLATFORM_OSX
    MPE_CORE_ASSERT(openGLVersionMajor >= 3 || (openGLVersionMajor >= 3 && openGLVersionMinor >= 1), "MPE REQUIRES OPENGLES VERSION 3.1 FOR macOS.");
#else
    MPE_CORE_ASSERT(openGLVersionMajor > 3 || (openGLVersionMajor == 3 && openGLVersionMinor >= 1), "MPE REQUIRES OPENGLES VERSION 3.1 OR GREATER.");
#endif

    graphicalContextProps->vendor = std::string(reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    graphicalContextProps->renderer = std::string(reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    graphicalContextProps->shaderTypeAmount = OPENGL_SHADER_TYPE_AMOUNT;

    MPE_CORE_INFO('\n' + m_settings->GetGraphicalContextPropsAsString());

    m_settings->SetVsync(false);
    m_settings->SetBlend(true);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_settings->SetDepthTest(true);
    m_settings->SetPolygonMode(false);
    m_settings->SetLimitFPS(false);
    m_settings->SetMaxFPS(60);
    m_settings->SetFaceCulling(false);
    m_settings->SetDebugOutput(true);

    MPE_CORE_WARN("Checking for any errors caused by settings...");
    glCheckError();
    MPE_CORE_WARN("Causing OpenGLES errors to test error handling...");

    // Not available in OpenGLES 3.1
    // if (m_settings->GetDebugOutput())
    //     glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1, GL_DEBUG_SEVERITY_NOTIFICATION, -1, "This is a debug test.");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_INVALID_ENUM);
    glCheckError();

    MPE_CORE_INFO("Settings initialized.");
}

void OpenGLESRendererAPI::Shutdown()
{
    delete m_settings;
}

void OpenGLESRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);
}

void OpenGLESRendererAPI::SetClearColor(const glm::vec4 &color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLESRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLESRendererAPI::DrawIndexed(const REF<VertexArray> &vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLESRendererAPI::DrawLines(const REF<VertexArray> &vertexArray, uint32_t vertexCount)
{
    glDrawArrays(GL_LINES, 0, static_cast<uint32_t>(vertexArray->GetVertexBuffers()[0]->GetSize() / sizeof(float) / vertexCount));
}

RenderSettings *OpenGLESRendererAPI::GetSettings()
{
    return m_settings;
}
}