#include "OpenGLESRendererAPI.h"
#include "MPE/MPEPCH.h"

#include <GLES3/gl31.h>

namespace MPE
{
void OpenGLESRendererAPI::Init()
{
    SYS_Settings = new OpenGLESSettings();

    SYS_Settings->SetVsync(false);
    SYS_Settings->SetBlend(true);
    SYS_Settings->SetDepthTest(true);
    SYS_Settings->SetPolygonMode(false);
    SYS_Settings->SetLimitFPS(false);
    SYS_Settings->SetMaxFPS(60);
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
    return SYS_Settings;
}
}