#include "Renderer2D.h"
#include "MPE/MPEPCH.h"

#include "MPE/Renderer/RenderPrimitive.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Shaders/Shader.h"

#include "MPE/Vendor/GLM/GLM.h"

// TODO: have a matrix class that has methods to translate, rotate, scale, shear and then you pass the matrix to the draw call.

namespace MPE
{
struct Renderer2DData
{
    REF<VertexArray> localVertexArray;
    REF<Shader> textureShader;
    REF<Texture2D> whiteTexture;
};

static Renderer2DData *m_rendererData;

void Renderer2D::Init()
{
    m_rendererData = new Renderer2DData;

    m_rendererData->localVertexArray = VertexArray::Create();
    float vertices[5 * 4] = {-0.75f, -0.75f, 0.0f, 0.0f, 0.0f, 0.75f,  -0.75f, 0.0f, 1.0f, 0.0f,
                             0.75f,  0.75f,  0.0f, 1.0f, 1.0f, -0.75f, 0.75f,  0.0f, 0.0f, 1.0f};

    REF<VertexBuffer> vertexBuffer;
    vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    vertexBuffer->SetLayout({{ShaderDataType::Vec3, "ATTR_POS"}, {ShaderDataType::Vec2, "ATTR_TEXCOORD"}});
    m_rendererData->localVertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
    REF<IndexBuffer> indexBuffer;
    indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_rendererData->localVertexArray->SetIndexBuffer(indexBuffer);

    m_rendererData->whiteTexture = Texture2D::Create(1, 1);
    uint32_t whiteTexData = 0xffffffff;
    m_rendererData->whiteTexture->SetData(&whiteTexData, sizeof(whiteTexData));

    m_rendererData->textureShader = Shader::Create("Data/Shaders/ColoredTexture.glsl", true);
    m_rendererData->textureShader->Bind();
    m_rendererData->textureShader->SetInt1("UNI_TEXTURE", 0);
}

void Renderer2D::Shutdown()
{
    delete (m_rendererData);
}

void Renderer2D::BeginScene(const OrthographicCamera &camera)
{
    m_rendererData->textureShader->Bind();
    m_rendererData->textureShader->SetMat4("UNI_VPM", camera.GetProjectionViewMatrix());
}

void Renderer2D::EndScene() {}

void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 color)
{
    DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 color)
{
    m_rendererData->whiteTexture->Bind();
    m_rendererData->textureShader->SetFloat4("UNI_COLOR", color);
    m_rendererData->textureShader->SetFloat1("UNI_TILING_FACTOR", 1.0f);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) /*ROTATION*/ * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    m_rendererData->textureShader->SetMat4("UNI_MODELMAT", transform);

    m_rendererData->localVertexArray->Bind();
    RenderPrimitive::DrawIndexed(m_rendererData->localVertexArray);
}

void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const REF<Texture2D> texture, float tillingFactor)
{
    // TODO: investigate => should this also bind textures?
    // m_rendererData->textureShader->SetFloat4("UNI_COLOR", glm::vec4(1.0f));
    // // m_rendererData->textureShader->SetFloat4("UNI_COLOR", glm::vec4(0.5f, 0.25f, 0.5f, 1.0f));
    // m_rendererData->textureShader->SetFloat1("UNI_TILING_FACTOR", tillingFactor);
    // texture->Bind();

    // glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f)) /*ROTATION*/ * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    // m_rendererData->textureShader->SetMat4("UNI_MODELMAT", transform);

    // m_rendererData->localVertexArray->Bind();
    // RenderPrimitive::DrawIndexed(m_rendererData->localVertexArray);

    DrawQuad({position.x, position.y, 0.0f}, size, texture, tillingFactor);
}

void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const REF<Texture2D> texture, float tillingFactor)
{
    m_rendererData->textureShader->SetFloat4("UNI_COLOR", glm::vec4(1.0f));
    // m_rendererData->textureShader->SetFloat4("UNI_COLOR", glm::vec4(0.5f, 0.25f, 0.5f, 1.0f));
    m_rendererData->textureShader->SetFloat1("UNI_TILING_FACTOR", tillingFactor);
    texture->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) /*ROTATION*/ * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    m_rendererData->textureShader->SetMat4("UNI_MODELMAT", transform);

    m_rendererData->localVertexArray->Bind();
    RenderPrimitive::DrawIndexed(m_rendererData->localVertexArray);
}
}