#include "OpenGLESGrid.h"
#include "MPE/MPEPCH.h"

#include "MPE/Renderer/RenderPrimitive.h"
#include "Platform/OpenGLES/Shaders/OpenGLESShader.h"

#include <GLES3/gl31.h>

namespace MPE
{
OpenGLESGrid::OpenGLESGrid() {}

void OpenGLESGrid::Init(float gridSize, float gridSpacing, MPE::OrthographicCamera& camera)
{
    Resize(gridSize, gridSpacing);

    m_mainCamera = &camera;

    m_shader = MPE::OpenGLESShader::Create("Data/Shaders/Editor/Grid/GridShader.glsl", true);
}

void OpenGLESGrid::Resize(float gridSize, float gridSpacing)
{
    if (gridSize <= 0)
    {
        MPE_CORE_ERROR("Grid size must be greater than 0.");
        return;
    }
    if (gridSpacing <= 0)
    {
        MPE_CORE_ERROR("Grid spacing must be greater than 0.");
        return;
    }

    m_size = gridSize;
    m_spacing = gridSpacing;

    // Create vertices for the grid
    std::vector<float> vertices;
    for (float i = -gridSize; i <= gridSize; i += gridSpacing)
    {
        // Lines parallel to Y-axis
        vertices.push_back(i);
        vertices.push_back(-gridSize);
        vertices.push_back(0.0f);

        vertices.push_back(i);
        vertices.push_back(gridSize);
        vertices.push_back(0.0f);

        // Lines parallel to X-axis
        vertices.push_back(-gridSize);
        vertices.push_back(i);
        vertices.push_back(0.0f);

        vertices.push_back(gridSize);
        vertices.push_back(i);
        vertices.push_back(0.0f);
    }

    m_vertexArray = MPE::OpenGLESVertexArray::Create();
    MPE::REF<MPE::VertexBuffer> vertexBuffer;
    vertexBuffer = MPE::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
    vertexBuffer->SetLayout({{MPE::ShaderDataType::Vec3, "ATTR_POS"}});
    m_vertexArray->AddVertexBuffer(vertexBuffer);
}

void OpenGLESGrid::DrawGrid()
{
    m_shader->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(m_shader)->InjectUniformMat4("UNI_VPM", m_mainCamera->GetProjectionViewMatrix());

    m_vertexArray->Bind();
    MPE::RenderPrimitive::DrawLines(m_vertexArray, 3);
}
}