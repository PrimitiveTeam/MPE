#include "SphereMeshGenerator.h"

#include "Editor/Editor/Ecs/Components/Meshes/MeshComponent.h"
#include "Editor/Editor/Ecs/Components/Meshes/Metadata/SphereMetadataComponent.h"
#include "Editor/Editor/Ecs/Components/Graphical/RenderComponent.h"

namespace MPE
{
namespace ECS
{
void SphereMeshGenerator::RegenerateRenderComponent(MeshComponent& mesh, SphereMetadataComponent& metadata, RenderComponent& renderComp)
{
    // Here we basically need to regenerate vertexarray and indexbuffers, here is what initially runs when instantiating the sphere (runs after calling sphere
    // generate)
    /*
        m_color = {0.6f, 0.6f, 0.6f, 1.0f};

    m_shader = ShaderLibrary::AddOrLoadIfExists("Data/Shaders/TextureWithNormals.glsl", true);
    // m_texture = MPE::Texture2D::Create("Data/Textures/earth2048.bmp");

    m_vertexArray = VertexArray::Create();

    REF<VertexBuffer> vertexBuffer =
        VertexBuffer::Create(m_meshComponent->interleavedVertices.data(), m_meshComponent->interleavedVertices.size() * sizeof(float));
    vertexBuffer->SetLayout({{ShaderDataType::Vec3, "ATTR_POS"}, {MPE::ShaderDataType::Vec3, "ATTR_NORMALS"}, {MPE::ShaderDataType::Vec2, "ATTR_TEXCOORD"}});
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    REF<IndexBuffer> indexBuffer = IndexBuffer::Create(m_meshComponent->indices.data(), m_meshComponent->indices.size());
    m_vertexArray->SetIndexBuffer(indexBuffer);

    m_ECS.AddComponentToEntity<ECS::RenderComponent>(m_entity, m_vertexArray, m_shader);
    m_ECS.AddComponentToEntity<ECS::MaterialComponent>(m_entity, glm::vec4(1.0f), "Data/Textures/earth2048.bmp");
    */
    // Now we need to adapt something similar here just using componenets

    REF<VertexBuffer> vertexBuffer = VertexBuffer::Create(mesh.interleavedVertices.data(), mesh.interleavedVertices.size() * sizeof(float));
    vertexBuffer->SetLayout({{ShaderDataType::Vec3, "ATTR_POS"}, {MPE::ShaderDataType::Vec3, "ATTR_NORMALS"}, {MPE::ShaderDataType::Vec2, "ATTR_TEXCOORD"}});
    renderComp.vertexArray->AddVertexBuffer(vertexBuffer);

    REF<IndexBuffer> indexBuffer = IndexBuffer::Create(mesh.indices.data(), mesh.indices.size());
    renderComp.vertexArray->SetIndexBuffer(indexBuffer);
}

void SphereMeshGenerator::GenerateSphere(float radius, uint32_t sectors, uint32_t stacks, bool smooth, unsigned char upAxis, unsigned int& stride,
                                         std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& textureCoordinates,
                                         std::vector<float>& interleavedVertices, std::vector<float>& indicesLines, std::vector<unsigned int>& indices)
{
    interleavedVertices.clear();

    if (smooth)
        GenerateSmoothVertices(radius, sectors, stacks, vertices, normals, textureCoordinates, indicesLines, indices);
    else
        GenerateFlatVertices(radius, sectors, stacks, vertices, normals, textureCoordinates, indicesLines, indices);

    GenerateInterleavedVertices(vertices, normals, textureCoordinates, interleavedVertices);

    if (upAxis != 3) SwitchUpAxis(vertices, normals, interleavedVertices, 3, upAxis);
}

void SphereMeshGenerator::SwitchUpAxis(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& interleavedVertices, unsigned int from,
                                       unsigned int to)
{
    // initial transform matrix cols
    float tx[] = {1.0f, 0.0f, 0.0f};  // x-axis (left)
    float ty[] = {0.0f, 1.0f, 0.0f};  // y-axis (up)
    float tz[] = {0.0f, 0.0f, 1.0f};  // z-axis (forward)

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
    std::size_t count = vertices.size();
    float vx, vy, vz;
    float nx, ny, nz;
    for (i = 0, j = 0; i < count; i += 3, j += 8)
    {
        // transform vertices
        vx = vertices[i];
        vy = vertices[i + 1];
        vz = vertices[i + 2];
        vertices[i] = tx[0] * vx + ty[0] * vy + tz[0] * vz;      // x
        vertices[i + 1] = tx[1] * vx + ty[1] * vy + tz[1] * vz;  // y
        vertices[i + 2] = tx[2] * vx + ty[2] * vy + tz[2] * vz;  // z

        // transform normals
        nx = normals[i];
        ny = normals[i + 1];
        nz = normals[i + 2];
        normals[i] = tx[0] * nx + ty[0] * ny + tz[0] * nz;      // nx
        normals[i + 1] = tx[1] * nx + ty[1] * ny + tz[1] * nz;  // ny
        normals[i + 2] = tx[2] * nx + ty[2] * ny + tz[2] * nz;  // nz

        // trnasform interleaved array
        interleavedVertices[j] = vertices[i];
        interleavedVertices[j + 1] = vertices[i + 1];
        interleavedVertices[j + 2] = vertices[i + 2];
        interleavedVertices[j + 3] = normals[i];
        interleavedVertices[j + 4] = normals[i + 1];
        interleavedVertices[j + 5] = normals[i + 2];
    }
}

void SphereMeshGenerator::SwitchSmoothness(float radius, unsigned char upAxis, uint32_t sectors, uint32_t stacks, std::vector<float>& vertices,
                                           std::vector<float>& normals, std::vector<float>& textureCoordinates, std::vector<float>& interleavedVertices,
                                           std::vector<float>& indicesLines, std::vector<unsigned int>& indices, bool smooth)
{
    interleavedVertices.clear();

    if (smooth)
        GenerateSmoothVertices(radius, sectors, stacks, vertices, normals, textureCoordinates, indicesLines, indices);
    else
        GenerateFlatVertices(radius, sectors, stacks, vertices, normals, textureCoordinates, indicesLines, indices);

    GenerateInterleavedVertices(vertices, normals, textureCoordinates, interleavedVertices);

    if (upAxis != 3) SwitchUpAxis(vertices, normals, interleavedVertices, 3, upAxis);
}

void SphereMeshGenerator::ReverseNormals(std::vector<float>& normals, std::vector<float>& interleavedVertices, std::vector<unsigned int>& indices)
{
    std::size_t i, j;
    std::size_t count = normals.size();
    for (i = 0, j = 3; i < count; i += 3, j += 8)
    {
        normals[i] *= -1;
        normals[i + 1] *= -1;
        normals[i + 2] *= -1;

        interleavedVertices[j] = normals[i];
        interleavedVertices[j + 1] = normals[i + 1];
        interleavedVertices[j + 2] = normals[i + 2];
    }

    unsigned int tmp;
    count = indices.size();
    for (i = 0; i < count; i += 3)
    {
        tmp = indices[i];
        indices[i] = indices[i + 2];
        indices[i + 2] = tmp;
    }
}

void SphereMeshGenerator::GenerateSmoothVertices(float radius, uint32_t sectors, uint32_t stacks, std::vector<float>& vertices, std::vector<float>& normals,
                                                 std::vector<float>& textureCoordinates, std::vector<float>& indicesLines, std::vector<unsigned int>& indices)
{
    // Clear all vectors
    vertices.clear();
    normals.clear();
    textureCoordinates.clear();
    indices.clear();
    indicesLines.clear();

    const float PI = glm::pi<float>();

    // vertex
    float x, y, z, xy;
    // normal
    float nx, ny, nz, inverseLength = 1.0f / radius;
    // texture coords
    float s, t;

    float sectorStep = 2 * PI / sectors;
    float stackStep = PI / stacks;
    float sectorAngle, stackAngle;

    for (uint32_t i = 0; i <= stacks; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; ++j)
        {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            AddVertex(vertices, x, y, z);

            nx = x * inverseLength;
            ny = y * inverseLength;
            nz = z * inverseLength;
            AddNormal(normals, nx, ny, nz);

            s = (float) j / sectors;
            t = (float) i / stacks;
            AddTexureCoord(textureCoordinates, s, t);
        }
    }

    unsigned int k1, k2;
    for (int i = 0; i < stacks; ++i)
    {
        k1 = i * (sectors + 1);
        k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                AddIndices(indices, k1, k2, k1 + 1);
            }

            if (i != (stacks - 1))
            {
                AddIndices(indices, k1 + 1, k2, k2 + 1);
            }

            indicesLines.push_back(k1);
            indicesLines.push_back(k2);

            if (i != 0)
            {
                indicesLines.push_back(k1);
                indicesLines.push_back(k1 + 1);
            }
        }
    }
}

void SphereMeshGenerator::GenerateFlatVertices(float radius, uint32_t sectors, uint32_t stacks, std::vector<float>& vertices, std::vector<float>& normals,
                                               std::vector<float>& textureCoordinates, std::vector<float>& indicesLines, std::vector<unsigned int>& indices)
{
    const float PI = glm::pi<float>();

    struct Vertex
    {
        float x, y, z, s, t;
    };
    std::vector<Vertex> temporaryVertices;

    float sectorStep = 2 * PI / sectors;
    float stackStep = PI / stacks;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stacks; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; ++j)
        {
            sectorAngle = j * sectorStep;

            Vertex vertex;
            vertex.x = xy * cosf(sectorAngle);
            vertex.y = xy * sinf(sectorAngle);
            vertex.z = z;
            vertex.s = (float) j / sectors;
            vertex.t = (float) i / stacks;
            temporaryVertices.push_back(vertex);
        }
    }

    // Clear all vectors
    vertices.clear();
    normals.clear();
    textureCoordinates.clear();
    indicesLines.clear();
    indices.clear();

    Vertex v1, v2, v3, v4;
    std::vector<float> n;

    int i, j, k, vi1, vi2;
    int index = 0;
    for (i = 0; i < stacks; ++i)
    {
        vi1 = i * (sectors + 1);
        vi2 = (i + 1) * (sectors + 1);

        for (j = 0; j < sectors; ++j, ++vi1, ++vi2)
        {
            v1 = temporaryVertices[vi1];
            v2 = temporaryVertices[vi2];
            v3 = temporaryVertices[vi1 + 1];
            v4 = temporaryVertices[vi2 + 1];

            if (i == 0)
            {
                AddVertex(vertices, v1.x, v1.y, v1.z);
                AddVertex(vertices, v2.x, v2.y, v2.z);
                AddVertex(vertices, v4.x, v4.y, v4.z);

                AddTexureCoord(textureCoordinates, v1.s, v1.t);
                AddTexureCoord(textureCoordinates, v2.s, v2.t);
                AddTexureCoord(textureCoordinates, v4.s, v4.t);

                n = GenerateFaceNormal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v4.x, v4.y, v4.z);
                for (k = 0; k < 3; ++k)
                {
                    AddNormal(normals, n[0], n[1], n[2]);
                }

                AddIndices(indices, index, index + 1, index + 2);

                indicesLines.push_back(index);
                indicesLines.push_back(index + 1);

                index += 3;
            }
            else if (i == (stacks - 1))
            {
                AddVertex(vertices, v1.x, v1.y, v1.z);
                AddVertex(vertices, v2.x, v2.y, v2.z);
                AddVertex(vertices, v3.x, v3.y, v3.z);

                AddTexureCoord(textureCoordinates, v1.s, v1.t);
                AddTexureCoord(textureCoordinates, v2.s, v2.t);
                AddTexureCoord(textureCoordinates, v3.s, v3.t);

                n = GenerateFaceNormal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
                for (k = 0; k < 3; ++k)
                {
                    AddNormal(normals, n[0], n[1], n[2]);
                }

                AddIndices(indices, index, index + 1, index + 2);

                indicesLines.push_back(index);
                indicesLines.push_back(index + 1);
                indicesLines.push_back(index);
                indicesLines.push_back(index + 2);

                index += 3;
            }
            else
            {
                AddVertex(vertices, v1.x, v1.y, v1.z);
                AddVertex(vertices, v2.x, v2.y, v2.z);
                AddVertex(vertices, v3.x, v3.y, v3.z);
                AddVertex(vertices, v4.x, v4.y, v4.z);

                AddTexureCoord(textureCoordinates, v1.s, v1.t);
                AddTexureCoord(textureCoordinates, v2.s, v2.t);
                AddTexureCoord(textureCoordinates, v3.s, v3.t);
                AddTexureCoord(textureCoordinates, v4.s, v4.t);

                n = GenerateFaceNormal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
                for (k = 0; k < 4; ++k)
                {
                    AddNormal(normals, n[0], n[1], n[2]);
                }

                AddIndices(indices, index, index + 1, index + 2);
                AddIndices(indices, index + 2, index + 1, index + 3);

                indicesLines.push_back(index);
                indicesLines.push_back(index + 1);
                indicesLines.push_back(index);
                indicesLines.push_back(index + 2);

                index += 4;
            }
        }
    }
}

std::vector<float> SphereMeshGenerator::GenerateFaceNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
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
        float inverseLength = 1.0f / length;
        normal[0] = nx * inverseLength;
        normal[1] = ny * inverseLength;
        normal[2] = nz * inverseLength;
    }

    return normal;
}

void SphereMeshGenerator::GenerateInterleavedVertices(std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& textureCoordinates,
                                                      std::vector<float>& interleavedVertices)
{
    std::size_t i, j;
    std::size_t count = vertices.size();
    for (i = 0, j = 0; i < count; i += 3, j += 2)
    {
        interleavedVertices.push_back(vertices[i]);
        interleavedVertices.push_back(vertices[i + 1]);
        interleavedVertices.push_back(vertices[i + 2]);

        interleavedVertices.push_back(normals[i]);
        interleavedVertices.push_back(normals[i + 1]);
        interleavedVertices.push_back(normals[i + 2]);

        interleavedVertices.push_back(textureCoordinates[j]);
        interleavedVertices.push_back(textureCoordinates[j + 1]);
    }
}

void SphereMeshGenerator::AddVertex(std::vector<float>& vertices, float x, float y, float z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}

void SphereMeshGenerator::AddNormal(std::vector<float>& normals, float nx, float ny, float nz)
{
    normals.push_back(nx);
    normals.push_back(ny);
    normals.push_back(nz);
}

void SphereMeshGenerator::AddTexureCoord(std::vector<float>& textureCoordinates, float s, float t)
{
    textureCoordinates.push_back(s);
    textureCoordinates.push_back(t);
}

void SphereMeshGenerator::AddIndices(std::vector<unsigned int>& indices, unsigned int i1, unsigned int i2, unsigned int i3)
{
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}

}
}