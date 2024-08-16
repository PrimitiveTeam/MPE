#include "OpenGLRendererAPI.h"
#include "MPE/MPEPCH.h"

#include "Platform/OpenGL/Utilities/OpenGLUtilities.h"

#include <glad/glad.h>

namespace MPE
{
void OpenGLRendererAPI::Init()
{
    m_settings = new OpenGLSettings();

    // std::string OpenGL_INFO = "\nOpenGL Info:\n";

    auto graphicalContextProps = m_settings->GetGraphicalContextProps();
    int OpenGLVersionMajor;
    int OpenGLVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersionMinor);

    // OpenGL_INFO += "\tOpenGL Version: " + std::to_string(OpenGLVersionMajor) + "." + std::to_string(OpenGLVersionMinor) + "\n";
    graphicalContextProps->m_majorVersion = OpenGLVersionMajor;
    graphicalContextProps->m_minorVersion = OpenGLVersionMinor;

#ifdef MPE_PLATFORM_WINDOWS
    MPE_CORE_ASSERT(OpenGLVersionMajor > 4 || (OpenGLVersionMajor == 4 && OpenGLVersionMinor >= 6), "MPE REQUIRES OPENGL VERSION 4.6 OR GREATER.");
#elif MPE_PLATFORM_OSX
    MPE_CORE_ASSERT(OpenGLVersionMajor >= 3 || (OpenGLVersionMajor >= 3 && OpenGLVersionMinor >= 2), "MPE REQUIRES OPENGL VERSION 3.2 FOR macOS.");
#else
    MPE_CORE_ASSERT(OpenGLVersionMajor > 4 || (OpenGLVersionMajor == 4 && OpenGLVersionMinor >= 6), "MPE REQUIRES OPENGL VERSION 4.6 OR GREATER.");
#endif

    graphicalContextProps->m_vendor = std::string(reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    graphicalContextProps->m_renderer = std::string(reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    graphicalContextProps->m_shaderTypeAmount = OPENGL_SHADER_TYPE_AMOUNT;

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
    MPE_CORE_WARN("Causing OpenGL errors to test error handling...");

    if (m_settings->GetDebugOutput())
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1, GL_DEBUG_SEVERITY_NOTIFICATION, -1, "This is a debug test.");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_INVALID_ENUM);
    glCheckError();

    MPE_CORE_INFO("Settings initialized.");
}

void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const REF<VertexArray> &vertexArray)
{
    MPE_CORE_ASSERT(vertexArray->GetIndexBuffer(), "VERTEX ARRAY HAS NO INDEX BUFFER");
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::DrawLines(const REF<VertexArray> &vertexArray, uint32_t vertexCount)
{
    glDrawArrays(GL_LINES, 0, static_cast<uint32_t>(vertexArray->GetVertexBuffers()[0]->GetSize() / sizeof(float) / vertexCount));
}

RenderSettings *OpenGLRendererAPI::GetSettings()
{
    return m_settings;
}
}