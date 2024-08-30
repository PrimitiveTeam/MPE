#include "Renderer.h"
#include "MPE/MPEPCH.h"

#include "MPE/Renderer/Renderer2D.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#ifdef MPE_OPENGL
#    include "Platform/OpenGL/Shaders/OpenGLShader.h"
#endif
#ifdef MPE_OPENGLES
#    include "Platform/OpenGLES/Shaders/OpenGLESShader.h"
#endif
namespace MPE
{
// GRAPHICS_API Renderer::SYS_RENDERER_API = GRAPHICS_API::OpenGL;

void Renderer::Init()
{
    RenderPrimitive::Init();
    Renderer2D::Init();
    ShaderLibrary::Init();
}

void Renderer::Shutdown()
{
    MPE_CORE_INFO("Renderer shutting down...");
    ShaderLibrary::Shutdown();
    RenderPrimitive::Shutdown();
    Renderer2D::Shutdown();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    RenderPrimitive::SetViewport(0, 0, width, height);
}

Renderer::SceneData *Renderer::m_scene = new Renderer::SceneData;
REF<WindowFpsMs> Renderer::m_windowFpsMs = NEWREF<WindowFpsMs>();

void Renderer::BeginScene(OrthographicCamera &camera)
{
    m_scene->projectionViewMatrix = camera.GetProjectionViewMatrix();
}

void Renderer::BeginScene(PerspectiveCamera &camera)
{
    m_scene->projectionViewMatrix = camera.GetProjectionViewMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const REF<Shader> &shader, const REF<VertexArray> &vertexArray, const glm::mat4 &transform)
{
    shader->Bind();

    auto api = RendererAPI::GetGraphicsAPI();

    switch (api)
    {
        case RendererAPI::API::OpenGL:
#ifdef MPE_OPENGL
            std::dynamic_pointer_cast<OpenGLShader>(shader)->InjectUniformMat4("UNI_VPM", m_scene->projectionViewMatrix);
            std::dynamic_pointer_cast<OpenGLShader>(shader)->InjectUniformMat4("UNI_MODELMAT", transform);
            break;
#else
            MPE_CORE_ASSERT(false, "OPENGL IS NOT SUPPORTED.");
            break;
#endif
        case RendererAPI::API::OpenGLES:
#ifdef MPE_OPENGLES
            std::dynamic_pointer_cast<OpenGLESShader>(shader)->InjectUniformMat4("UNI_VPM", m_scene->projectionViewMatrix);
            std::dynamic_pointer_cast<OpenGLESShader>(shader)->InjectUniformMat4("UNI_MODELMAT", transform);
            break;
#else
            MPE_CORE_ASSERT(false, "OPENGLES IS NOT SUPPORTED.");
            break;
#endif
        default:
            MPE_CORE_ASSERT(false, "UNKOWN RENDERER API.");
            break;
    }

    vertexArray->Bind();
    RenderPrimitive::DrawIndexed(vertexArray);
}
}