#include "Renderer.h"
#include "MPE/MPEPCH.h"

#include "MPE/Platform/OpenGL/Shaders/OpenGLShader.h"
#include "MPE/Renderer/Renderer2D.h"

namespace MPE
{
// GRAPHICS_API Renderer::SYS_RENDERER_API = GRAPHICS_API::OpenGL;

void Renderer::Init()
{
    RenderPrimitive::Init();
    Renderer2D::Init();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    RenderPrimitive::SetViewport(0, 0, width, height);
}

Renderer::SceneData *Renderer::SYS_SCENE = new Renderer::SceneData;

void Renderer::BeginScene(OrthographicCamera &camera)
{
    SYS_SCENE->PROJECTION_VIEW_MATRIX = camera.GetProjectionViewMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const REF<Shader> &shader, const REF<VertexArray> &vertexArray, const glm::mat4 &transform)
{
    shader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->InjectUniformMat4("UNI_VPM", SYS_SCENE->PROJECTION_VIEW_MATRIX);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->InjectUniformMat4("UNI_MODELMAT", transform);

    vertexArray->Bind();
    RenderPrimitive::DrawIndexed(vertexArray);
}
}