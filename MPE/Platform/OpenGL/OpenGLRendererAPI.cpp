#include "OpenGLRendererAPI.h"
#include "MPE/MPEPCH.h"

#include <glad/glad.h>

namespace MPE
{
void OpenGLRendererAPI::Init()
{
    SYS_Settings = new OpenGLSettings();

    SYS_Settings->SetVsync(true);
    SYS_Settings->SetBlend(true);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    SYS_Settings->SetDepthTest(true);
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
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
}