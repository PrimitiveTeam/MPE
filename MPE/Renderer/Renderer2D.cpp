#include "Renderer2D.h"
#include "MPE/MPEPCH.h"

#include "MPE/Renderer/RenderPrimitive.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/Shaders/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO: have a matrix class that has methods to translate, rotate, scale, shear and then you pass the matrix to the draw call.

namespace MPE
{
struct Renderer2DData
{
    REF<VertexArray> LOCAL_VERTEX_ARRAY;
    REF<Shader> TEXTURE_SHADER;
    REF<Texture2D> WHITE_TEXTURE;
};

static Renderer2DData *SYS_DATA;

void Renderer2D::Init()
{
    SYS_DATA = new Renderer2DData;

    SYS_DATA->LOCAL_VERTEX_ARRAY = VertexArray::Create();
    float vertices[5 * 4] = {-0.75f, -0.75f, 0.0f, 0.0f, 0.0f, 0.75f,  -0.75f, 0.0f, 1.0f, 0.0f,
                             0.75f,  0.75f,  0.0f, 1.0f, 1.0f, -0.75f, 0.75f,  0.0f, 0.0f, 1.0f};

    REF<VertexBuffer> vertexBuffer;
    vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    vertexBuffer->SetLayout({{ShaderDataType::Vec3, "ATTR_POS"}, {ShaderDataType::Vec2, "ATTR_TEXCOORD"}});
    SYS_DATA->LOCAL_VERTEX_ARRAY->AddVertexBuffer(vertexBuffer);

    uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
    REF<IndexBuffer> indexBuffer;
    indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    SYS_DATA->LOCAL_VERTEX_ARRAY->SetIndexBuffer(indexBuffer);

    SYS_DATA->WHITE_TEXTURE = Texture2D::Create(1, 1);
    uint32_t WhiteTexData = 0xffffffff;
    SYS_DATA->WHITE_TEXTURE->SetData(&WhiteTexData, sizeof(WhiteTexData));

    SYS_DATA->TEXTURE_SHADER = Shader::Create("Data/Shaders/ColoredTexture.glsl");
    SYS_DATA->TEXTURE_SHADER->Bind();
    SYS_DATA->TEXTURE_SHADER->SetInt1("UNI_TEXTURE", 0);
}

void Renderer2D::Shutdown()
{
    delete (SYS_DATA);
}

void Renderer2D::BeginScene(const OrthographicCamera &camera)
{
    SYS_DATA->TEXTURE_SHADER->Bind();
    SYS_DATA->TEXTURE_SHADER->SetMat4("UNI_VPM", camera.GetProjectionViewMatrix());
}

void Renderer2D::EndScene() {}

void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 color)
{
    DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 color)
{
    SYS_DATA->WHITE_TEXTURE->Bind();
    SYS_DATA->TEXTURE_SHADER->SetFloat4("UNI_COLOR", color);
    SYS_DATA->TEXTURE_SHADER->SetFloat1("UNI_TILING_FACTOR", 1.0f);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) /*ROTATION*/ * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    SYS_DATA->TEXTURE_SHADER->SetMat4("UNI_MODELMAT", transform);

    SYS_DATA->LOCAL_VERTEX_ARRAY->Bind();
    RenderPrimitive::DrawIndexed(SYS_DATA->LOCAL_VERTEX_ARRAY);
}

void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const REF<Texture2D> texture, float tillingFactor)
{
    DrawQuad({position.x, position.y, 0.0f}, size, texture, tillingFactor);
}

void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const REF<Texture2D> texture, float tillingFactor)
{
    SYS_DATA->TEXTURE_SHADER->SetFloat4("UNI_COLOR", glm::vec4(1.0f));
    // SYS_DATA->TEXTURE_SHADER->SetFloat4("UNI_COLOR", glm::vec4(0.5f, 0.25f, 0.5f, 1.0f));
    SYS_DATA->TEXTURE_SHADER->SetFloat1("UNI_TILING_FACTOR", tillingFactor);
    texture->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) /*ROTATION*/ * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    SYS_DATA->TEXTURE_SHADER->SetMat4("UNI_MODELMAT", transform);

    SYS_DATA->LOCAL_VERTEX_ARRAY->Bind();
    RenderPrimitive::DrawIndexed(SYS_DATA->LOCAL_VERTEX_ARRAY);
}
}