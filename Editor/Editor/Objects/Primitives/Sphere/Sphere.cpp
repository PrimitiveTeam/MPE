#include "Sphere.h"

#include "MPE/Log/GlobalLog.h"
#include "MPE/Renderer/Renderer.h"
#include "Editor/Editor/ECS/Utility/RotationUtilities.h"

#ifdef MPE_OPENGL
#    include "MPE/MPE_GFX_OPEN_GL.h"
#elif MPE_OPENGLES
#    include "MPE/MPE_GFX_OPEN_GLES.h"
#endif

#include <imgui.h>
#include "MPE/Vendor/GLM/GLM.h"

namespace MPE
{
const unsigned char MINIMUM_SECTORS = 2;
const unsigned char MINIMUM_STACKS = 2;

Sphere::Sphere(ECS::ECS& ecs) : Object(ecs)
{
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    Init();
}

Sphere::Sphere(ECS::ECS& ecs, const glm::vec3& position, const glm::vec3& scale) : Object(ecs)
{
    // Create an entity and add a transform component
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, position, glm::vec3(0.0f), scale);

    Init();
}

Sphere::Sphere(ECS::ECS& ecs, const glm::vec3& position, const glm::vec3& scale, float radius, uint32_t sectors, uint32_t stacks, bool smooth, int upAxis)
    : Object(ecs), m_interleavedStride(32)
{
    m_transform = &m_ECS.AddComponentToEntity<ECS::TransformComponent>(m_entity, position, glm::vec3(0.0f), scale);

    RecalculateSphere(radius, sectors, stacks, smooth, upAxis);
}

void Sphere::OnUpdate(Time deltaTime)
{
    if (m_autoRotate)
    {
        float deltaAngle = m_rotateSpeed * deltaTime.GetSeconds();
        m_eulerRotation.x += deltaAngle;
        m_eulerRotation.y += deltaAngle;
        m_eulerRotation.z += deltaAngle;

        m_eulerRotation.x = fmod(m_eulerRotation.x, m_maxAngle);
        m_eulerRotation.y = fmod(m_eulerRotation.y, m_maxAngle);
        m_eulerRotation.z = fmod(m_eulerRotation.z, m_maxAngle);

        m_transform->rotation = MPE::ECS::RotationUtilities::EulerToQuaternion(m_eulerRotation);
    }
}

void Sphere::OnRender(OrthographicCamera& camera)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_transform->position);
    transform *= glm::toMat4(m_transform->rotation);
    transform = glm::scale(transform, m_transform->scale);

    m_shader->Bind();

#ifdef MPE_OPENGL
    // std::dynamic_pointer_cast<MPE::OpenGLShader>(m_shader)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLShader>(m_shader)->InjectUniformFloat4("UNI_COLOR", m_color);
#elif MPE_OPENGLES
    // std::dynamic_pointer_cast<MPE::OpenGLESShader>(m_shader)->Bind();
    std::dynamic_pointer_cast<MPE::OpenGLESShader>(m_shader)->InjectUniformFloat4("UNI_COLOR", m_color);
#endif

    m_vertexArray->Bind();
    Renderer::BeginScene(camera);
    if (m_lineDrawing)
        Renderer::SubmitLines(m_shader, m_vertexArray, transform);
    else
        Renderer::Submit(m_shader, m_vertexArray, transform);
    Renderer::EndScene();
}

void Sphere::OnImGuiRender()
{
    ImGui::Text("Sphere Controls");
    ImGui::Checkbox("Auto Rotate", &m_autoRotate);
    if (ImGui::SliderFloat("Rotate X", &m_eulerRotation.x, -m_maxAngle, m_maxAngle) |
        ImGui::SliderFloat("Rotate Y", &m_eulerRotation.y, -m_maxAngle, m_maxAngle) |
        ImGui::SliderFloat("Rotate Z", &m_eulerRotation.z, -m_maxAngle, m_maxAngle))
    {
        m_transform->rotation = MPE::ECS::RotationUtilities::EulerToQuaternion(m_eulerRotation);
    }
    ImGui::SliderFloat3("Position", &m_transform->position.x, -10.0f, 10.0f);

    ImGui::Separator();
    ImGui::Text("Sphere Properties");

    bool tempLineDrawing = m_lineDrawing;
    if (ImGui::Checkbox("Line Drawing", &tempLineDrawing))
    {
        SetLineDrawing(tempLineDrawing);
    }

    if (ImGui::Button("Reverse Normals"))
    {
        ReverseNormals();
    }

    ImGui::ColorEdit4("Color", &m_color.r);

    auto tempRadius = m_radius;
    if (ImGui::SliderFloat("Radius", &tempRadius, 0.1f, 10.0f))
    {
        SetRadius(tempRadius);
    }

    auto tempSectors = m_sectors;
    if (ImGui::SliderInt("Sectors", (int*) &tempSectors, 2, 100))
    {
        SetSectors(tempSectors);
    }

    auto tempStacks = m_stacks;
    if (ImGui::SliderInt("Stacks", (int*) &tempStacks, 2, 100))
    {
        SetStacks(tempStacks);
    }

    auto tempUpAxis = m_upAxis;
    if (ImGui::SliderInt("Up Axis", (int*) &tempUpAxis, 1, 3))
    {
        SetUpAxis(tempUpAxis);
    }

    bool tempSmooth = m_smooth;
    if (ImGui::Checkbox("Smooth", &tempSmooth))
    {
        SetSmooth(tempSmooth);
    }
}

void Sphere::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
}

void Sphere::Init()
{
    m_color = {0.6f, 0.6f, 0.6f, 1.0f};

    m_shader = ShaderLibrary::AddOrLoadIfExists("Data/Shaders/FlatColor.glsl", true);

    m_vertexArray = VertexArray::Create();

    REF<VertexBuffer> vertexBuffer = VertexBuffer::Create(m_vertices.data(), m_vertices.size() * sizeof(float));
    vertexBuffer->SetLayout({{ShaderDataType::Vec3, "ATTR_POS"}});
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    REF<IndexBuffer> indexBuffer = IndexBuffer::Create(m_indices.data(), m_indices.size());
    m_vertexArray->SetIndexBuffer(indexBuffer);
}

void Sphere::SetRadius(float radius)
{
    if (m_radius == radius) return;

    RecalculateSphere(radius, m_sectors, m_stacks, m_smooth, m_upAxis);
}

void Sphere::SetSectors(uint32_t sectors)
{
    if (m_sectors == sectors) return;

    RecalculateSphere(m_radius, sectors, m_stacks, m_smooth, m_upAxis);
}

void Sphere::SetStacks(uint32_t stacks)
{
    if (m_stacks == stacks) return;

    RecalculateSphere(m_radius, m_sectors, stacks, m_smooth, m_upAxis);
}

void Sphere::SetUpAxis(uint32_t upAxis)
{
    // TODO: Just make a enum for this
    if (m_upAxis == upAxis || upAxis < 1 || upAxis > 3) return;

    SwitchUpAxis(m_upAxis, upAxis);
    m_upAxis = upAxis;
}

void Sphere::SetSmooth(bool smooth)
{
    if (m_smooth == smooth) return;

    this->m_smooth = smooth;
    if (m_smooth)
        GenerateSmoothVertices();
    else
        GenerateFlatVertices();
}

void Sphere::ReverseNormals()
{
    std::size_t i, j;
    std::size_t count = m_normals.size();
    for (i = 0, j = 3; i < count; i += 3, j += 8)
    {
        m_normals[i] *= -1;
        m_normals[i + 1] *= -1;
        m_normals[i + 2] *= -1;

        m_interleavedVertices[j] = m_normals[i];
        m_interleavedVertices[j + 1] = m_normals[i + 1];
        m_interleavedVertices[j + 2] = m_normals[i + 2];
    }

    unsigned int tmp;
    count = m_indices.size();
    for (i = 0; i < count; i += 3)
    {
        tmp = m_indices[i];
        m_indices[i] = m_indices[i + 2];
        m_indices[i + 2] = tmp;
    }
}

void Sphere::RecalculateSphere(float radius, uint32_t sectors, uint32_t stacks, bool smooth, int upAxis)
{
    MPE_ASSERT(radius > 0, "Sphere radius must be greater than 0");
    this->m_radius = radius;

    MPE_ASSERT(sectors >= MINIMUM_SECTORS, "Sphere sectors must be greater than or equal to 2");
    this->m_sectors = sectors;

    MPE_ASSERT(stacks >= MINIMUM_STACKS, "Sphere stacks must be greater than or equal to 2");
    this->m_stacks = stacks;

    this->m_smooth = smooth;

    MPE_ASSERT(upAxis >= 1 && upAxis <= 3, "Sphere up axis must be between 1 and 3");
    this->m_upAxis = upAxis;

    GenerateVertices();

    Init();
}

void Sphere::EnsureCleanArrays()
{
    m_vertices.clear();
    m_normals.clear();
    m_textureCoords.clear();
    m_indices.clear();
    m_indicesLines.clear();
}

void Sphere::AddVertex(float x, float y, float z)
{
    m_vertices.push_back(x);
    m_vertices.push_back(y);
    m_vertices.push_back(z);
}

void Sphere::AddNormal(float nx, float ny, float nz)
{
    m_normals.push_back(nx);
    m_normals.push_back(ny);
    m_normals.push_back(nz);
}

void Sphere::AddTexureCoord(float s, float t)
{
    m_textureCoords.push_back(s);
    m_textureCoords.push_back(t);
}

void Sphere::AddIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
    m_indices.push_back(i1);
    m_indices.push_back(i2);
    m_indices.push_back(i3);
}

void Sphere::SwitchUpAxis(unsigned int from, unsigned int to)
{
    float tx[] = {1.0f, 0.0f, 0.0f};
    float ty[] = {0.0f, 1.0f, 0.0f};
    float tz[] = {0.0f, 0.0f, 1.0f};

    // X -> Y
    if (from == 1 && to == 2)
    {
        tx[0] = 0.0f;
        tx[1] = 1.0f;
        ty[0] = -1.0f;
        ty[1] = 0.0f;
    }
    // X -> Z
    else if (from == 1 && to == 3)
    {
        tx[0] = 0.0f;
        tx[2] = 1.0f;
        tz[0] = -1.0f;
        tz[2] = 0.0f;
    }
    // Y -> X
    else if (from == 2 && to == 1)
    {
        tx[0] = 0.0f;
        tx[1] = -1.0f;
        ty[0] = 1.0f;
        ty[1] = 0.0f;
    }
    // Y -> Z
    else if (from == 2 && to == 3)
    {
        ty[1] = 0.0f;
        ty[2] = 1.0f;
        tz[1] = -1.0f;
        tz[2] = 0.0f;
    }
    //  Z -> X
    else if (from == 3 && to == 1)
    {
        tx[0] = 0.0f;
        tx[2] = -1.0f;
        tz[0] = 1.0f;
        tz[2] = 0.0f;
    }
    // Z -> Y
    else
    {
        ty[1] = 0.0f;
        ty[2] = -1.0f;
        tz[1] = 1.0f;
        tz[2] = 0.0f;
    }

    std::size_t i, j;
    std::size_t count = m_vertices.size();
    float vx, vy, vz;
    float nx, ny, nz;
    for (i = 0, j = 0; i < count; i += 3, j += 8)
    {
        // vertices
        vx = m_vertices[i];
        vy = m_vertices[i + 1];
        vz = m_vertices[i + 2];
        m_vertices[i] = tx[0] * vx + ty[0] * vy + tz[0] * vz;
        m_vertices[i + 1] = tx[1] * vx + ty[1] * vy + tz[1] * vz;
        m_vertices[i + 2] = tx[2] * vx + ty[2] * vy + tz[2] * vz;

        // normals
        nx = m_normals[i];
        ny = m_normals[i + 1];
        nz = m_normals[i + 2];
        m_normals[i] = tx[0] * nx + ty[0] * ny + tz[0] * nz;
        m_normals[i + 1] = tx[1] * nx + ty[1] * ny + tz[1] * nz;
        m_normals[i + 2] = tx[2] * nx + ty[2] * ny + tz[2] * nz;

        // interleaved
        m_interleavedVertices[j] = m_vertices[i];
        m_interleavedVertices[j + 1] = m_vertices[i + 1];
        m_interleavedVertices[j + 2] = m_vertices[i + 2];
        m_interleavedVertices[j + 3] = m_normals[i];
        m_interleavedVertices[j + 4] = m_normals[i + 1];
        m_interleavedVertices[j + 5] = m_normals[i + 2];
    }
}

void Sphere::GenerateVertices()
{
    if (m_smooth)
        GenerateSmoothVertices();
    else
        GenerateFlatVertices();
}

void Sphere::GenerateSmoothVertices()
{
    const float PI = glm::pi<float>();

    EnsureCleanArrays();

    // vertex
    float x, y, z, xy;
    // normal
    float nx, ny, nz, inverseLength = 1.0f / m_radius;
    // texture coords
    float s, t;

    float sectorStep = 2 * PI / m_sectors;
    float stackStep = PI / m_stacks;
    float sectorAngle, stackAngle;

    for (uint32_t i = 0; i <= m_stacks; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;
        xy = m_radius * cosf(stackAngle);
        z = m_radius * sinf(stackAngle);

        for (int j = 0; j <= m_sectors; ++j)
        {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            this->AddVertex(x, y, z);

            nx = x * inverseLength;
            ny = y * inverseLength;
            nz = z * inverseLength;
            this->AddNormal(nx, ny, nz);

            s = (float) j / m_sectors;
            t = (float) i / m_stacks;
            this->AddTexureCoord(s, t);
        }
    }

    unsigned int k1, k2;
    for (int i = 0; i < m_stacks; ++i)
    {
        k1 = i * (m_sectors + 1);
        k2 = k1 + m_sectors + 1;

        for (int j = 0; j < m_sectors; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                this->AddIndices(k1, k2, k1 + 1);
            }

            if (i != (m_stacks - 1))
            {
                this->AddIndices(k1 + 1, k2, k2 + 1);
            }

            m_indicesLines.push_back(k1);
            m_indicesLines.push_back(k2);

            if (i != 0)
            {
                m_indicesLines.push_back(k1);
                m_indicesLines.push_back(k1 + 1);
            }
        }
    }

    GenerateInterleavedVertices();

    if (this->m_upAxis != 3) SwitchUpAxis(3, this->m_upAxis);
}

void Sphere::GenerateFlatVertices()
{
    const float PI = glm::pi<float>();

    struct Vertex
    {
        float x, y, z, s, t;
    };
    std::vector<Vertex> temporaryVertices;

    float sectorStep = 2 * PI / m_sectors;
    float stackStep = PI / m_stacks;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= m_stacks; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;
        float xy = m_radius * cosf(stackAngle);
        float z = m_radius * sinf(stackAngle);

        for (int j = 0; j <= m_sectors; ++j)
        {
            sectorAngle = j * sectorStep;

            Vertex vertex;
            vertex.x = xy * cosf(sectorAngle);
            vertex.y = xy * sinf(sectorAngle);
            vertex.z = z;
            vertex.s = (float) j / m_sectors;
            vertex.t = (float) i / m_stacks;
            temporaryVertices.push_back(vertex);
        }
    }

    EnsureCleanArrays();

    Vertex v1, v2, v3, v4;
    std::vector<float> n;

    int i, j, k, vi1, vi2;
    int index = 0;
    for (i = 0; i < m_stacks; ++i)
    {
        vi1 = i * (m_sectors + 1);
        vi2 = (i + 1) * (m_sectors + 1);

        for (j = 0; j < m_sectors; ++j, ++vi1, ++vi2)
        {
            v1 = temporaryVertices[vi1];
            v2 = temporaryVertices[vi2];
            v3 = temporaryVertices[vi1 + 1];
            v4 = temporaryVertices[vi2 + 1];

            if (i == 0)
            {
                this->AddVertex(v1.x, v1.y, v1.z);
                this->AddVertex(v2.x, v2.y, v2.z);
                this->AddVertex(v4.x, v4.y, v4.z);

                this->AddTexureCoord(v1.s, v1.t);
                this->AddTexureCoord(v2.s, v2.t);
                this->AddTexureCoord(v4.s, v4.t);

                n = GenerateFaceNormal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v4.x, v4.y, v4.z);
                for (k = 0; k < 3; ++k)
                {
                    this->AddNormal(n[0], n[1], n[2]);
                }

                this->AddIndices(index, index + 1, index + 2);

                m_indicesLines.push_back(index);
                m_indicesLines.push_back(index + 1);

                index += 3;
            }
            else if (i == (m_stacks - 1))
            {
                this->AddVertex(v1.x, v1.y, v1.z);
                this->AddVertex(v2.x, v2.y, v2.z);
                this->AddVertex(v3.x, v3.y, v3.z);

                this->AddTexureCoord(v1.s, v1.t);
                this->AddTexureCoord(v2.s, v2.t);
                this->AddTexureCoord(v3.s, v3.t);

                n = GenerateFaceNormal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
                for (k = 0; k < 3; ++k)
                {
                    this->AddNormal(n[0], n[1], n[2]);
                }

                this->AddIndices(index, index + 1, index + 2);

                m_indicesLines.push_back(index);
                m_indicesLines.push_back(index + 1);
                m_indicesLines.push_back(index);
                m_indicesLines.push_back(index + 2);

                index += 3;
            }
            else
            {
                this->AddVertex(v1.x, v1.y, v1.z);
                this->AddVertex(v2.x, v2.y, v2.z);
                this->AddVertex(v3.x, v3.y, v3.z);
                this->AddVertex(v4.x, v4.y, v4.z);

                this->AddTexureCoord(v1.s, v1.t);
                this->AddTexureCoord(v2.s, v2.t);
                this->AddTexureCoord(v3.s, v3.t);
                this->AddTexureCoord(v4.s, v4.t);

                n = GenerateFaceNormal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
                for (k = 0; k < 4; ++k)
                {
                    this->AddNormal(n[0], n[1], n[2]);
                }

                this->AddIndices(index, index + 1, index + 2);
                this->AddIndices(index + 2, index + 1, index + 3);

                m_indicesLines.push_back(index);
                m_indicesLines.push_back(index + 1);
                m_indicesLines.push_back(index);
                m_indicesLines.push_back(index + 2);

                index += 4;
            }
        }
    }

    GenerateInterleavedVertices();

    if (this->m_upAxis != 3) SwitchUpAxis(3, this->m_upAxis);
}

void Sphere::GenerateInterleavedVertices()
{
    m_interleavedVertices.clear();

    std::size_t i, j;
    std::size_t count = m_vertices.size();
    for (i = 0, j = 0; i < count; i += 3, j += 2)
    {
        m_interleavedVertices.push_back(m_vertices[i]);
        m_interleavedVertices.push_back(m_vertices[i + 1]);
        m_interleavedVertices.push_back(m_vertices[i + 2]);

        m_interleavedVertices.push_back(m_normals[i]);
        m_interleavedVertices.push_back(m_normals[i + 1]);
        m_interleavedVertices.push_back(m_normals[i + 2]);

        m_interleavedVertices.push_back(m_textureCoords[j]);
        m_interleavedVertices.push_back(m_textureCoords[j + 1]);
    }
}

std::vector<float> Sphere::GenerateFaceNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
    const float EPSILON = 0.000001f;

    std::vector<float> normal(3, 0.0f);
    float nx, ny, nz;

    float ex1 = x2 - x1;
    float ey1 = y2 - y1;
    float ez1 = z2 - z1;
    float ex2 = x3 - x1;
    float ey2 = y3 - y1;
    float ez2 = z3 - z1;

    nx = ey1 * ez2 - ez1 * ey2;
    ny = ez1 * ex2 - ex1 * ez2;
    nz = ex1 * ey2 - ey1 * ex2;

    float length = sqrtf(nx * nx + ny * ny + nz * nz);
    if (length > EPSILON)
    {
        float lengthInv = 1.0f / length;
        normal[0] = nx * lengthInv;
        normal[1] = ny * lengthInv;
        normal[2] = nz * lengthInv;
    }

    return normal;
}

glm::vec4& Sphere::GetColor()
{
    return m_color;
}

void Sphere::SetColor(const glm::vec4& color)
{
    m_color = color;
}
}