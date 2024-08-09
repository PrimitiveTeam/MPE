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

    mainCamera = &camera;

    gridShader = MPE::OpenGLESShader::Create("Data/Shaders/Editor/Grid/GridShader.glsl", true);
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

    this->gridSize = gridSize;
    this->gridSpacing = gridSpacing;

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

    vertexArray = MPE::OpenGLESVertexArray::Create();
    MPE::REF<MPE::VertexBuffer> vertexBuffer;
    vertexBuffer = MPE::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
    vertexBuffer->SetLayout({{MPE::ShaderDataType::Vec3, "ATTR_POS"}});
    vertexArray->AddVertexBuffer(vertexBuffer);
}

void OpenGLESGrid::DrawGrid()
{
    gridShader->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(gridShader)->InjectUniformMat4("UNI_VPM", mainCamera->GetProjectionViewMatrix());

    vertexArray->Bind();
    MPE::RenderPrimitive::DrawLines(vertexArray, 3);
}
}