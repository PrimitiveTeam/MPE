#include "OpenGLRendererAPI.h"
#include "MPE/MPEPCH.h"

#include "Platform/OpenGL/Utilities/OpenGLUtilities.h"

#include <glad/glad.h>

namespace MPE
{
void OpenGLRendererAPI::Init()
{
    SYS_Settings = new OpenGLSettings();

    SYS_Settings->SetVsync(false);
    SYS_Settings->SetBlend(true);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    SYS_Settings->SetDepthTest(true);
    SYS_Settings->SetPolygonMode(false);
    SYS_Settings->SetLimitFPS(false);
    SYS_Settings->SetMaxFPS(60);
    SYS_Settings->SetFaceCulling(false);
    SYS_Settings->SetDebugOutput(true);

    MPE_CORE_WARN("Causing OpenGL errors to test error handling.");

    if (SYS_Settings->GetDebugOutput())
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
    return SYS_Settings;
}
}