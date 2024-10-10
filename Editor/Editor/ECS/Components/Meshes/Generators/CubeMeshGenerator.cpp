#include "CubeMeshGenerator.h"

namespace MPE
{
namespace ECS
{
void CubeMeshGenerator::GenerateCube(unsigned int& stride, std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& textureCoordinates,
                                     std::vector<float>& interleavedVertices, std::vector<unsigned int>& indices)
{
    // clean all vectors
    vertices.clear();
    normals.clear();
    textureCoordinates.clear();
    interleavedVertices.clear();

    // ATTR_POS (VEC3)
    stride = 0;
    stride += 12;
    vertices = {// I
                -0.5f, -0.5f, -0.5f,
                //
                0.5f, -0.5f, -0.5f,
                //
                0.5f, 0.5f, -0.5f,
                //
                0.5f, 0.5f, -0.5f,
                //
                -0.5f, 0.5f, -0.5f,
                //
                -0.5f, -0.5f, -0.5f,
                // II
                -0.5f, -0.5f, 0.5f,
                //
                0.5f, -0.5f, 0.5f,
                //
                0.5f, 0.5f, 0.5f,
                //
                0.5f, 0.5f, 0.5f,
                //
                -0.5f, 0.5f, 0.5f,
                //
                -0.5f, -0.5f, 0.5f,
                // III
                -0.5f, 0.5f, 0.5f,
                //
                -0.5f, 0.5f, -0.5f,
                //
                -0.5f, -0.5f, -0.5f,
                //
                -0.5f, -0.5f, -0.5f,
                //
                -0.5f, -0.5f, 0.5f,
                //
                -0.5f, 0.5f, 0.5f,
                // IV
                0.5f, 0.5f, 0.5f,
                //
                0.5f, 0.5f, -0.5f,
                //
                0.5f, -0.5f, -0.5f,
                //
                0.5f, -0.5f, -0.5f,
                //
                0.5f, -0.5f, 0.5f,
                //
                0.5f, 0.5f, 0.5f,
                // V
                -0.5f, -0.5f, -0.5f,
                //
                0.5f, -0.5f, -0.5f,
                //
                0.5f, -0.5f, 0.5f,
                //
                0.5f, -0.5f, 0.5f,
                //
                -0.5f, -0.5f, 0.5f,
                //
                -0.5f, -0.5f, -0.5f,
                // VI
                -0.5f, 0.5f, -0.5f,
                //
                0.5f, 0.5f, -0.5f,
                //
                0.5f, 0.5f, 0.5f,
                //
                0.5f, 0.5f, 0.5f,
                //
                -0.5f, 0.5f, 0.5f,
                //
                -0.5f, 0.5f, -0.5f};
    // ATTR_NORMAL (VEC3)
    stride += 12;
    normals = {// I
               0.0f, 0.0f, -1.0f,
               //
               0.0f, 0.0f, -1.0f,
               //
               0.0f, 0.0f, -1.0f,
               //
               0.0f, 0.0f, -1.0f,
               //
               0.0f, 0.0f, -1.0f,
               //
               0.0f, 0.0f, -1.0f,
               // II
               0.0f, 0.0f, 1.0f,
               //
               0.0f, 0.0f, 1.0f,
               //
               0.0f, 0.0f, 1.0f,
               //
               0.0f, 0.0f, 1.0f,
               //
               0.0f, 0.0f, 1.0f,
               //
               0.0f, 0.0f, 1.0f,
               // III
               -1.0f, 0.0f, 0.0f,
               //
               -1.0f, 0.0f, 0.0f,
               //
               -1.0f, 0.0f, 0.0f,
               //
               -1.0f, 0.0f, 0.0f,
               //
               -1.0f, 0.0f, 0.0f,
               //
               -1.0f, 0.0f, 0.0f,
               // IV
               1.0f, 0.0f, 0.0f,
               //
               1.0f, 0.0f, 0.0f,
               //
               1.0f, 0.0f, 0.0f,
               //
               1.0f, 0.0f, 0.0f,
               //
               1.0f, 0.0f, 0.0f,
               //
               1.0f, 0.0f, 0.0f,
               // V
               0.0f, -1.0f, 0.0f,
               //
               0.0f, -1.0f, 0.0f,
               //
               0.0f, -1.0f, 0.0f,
               //
               0.0f, -1.0f, 0.0f,
               //
               0.0f, -1.0f, 0.0f,
               //
               0.0f, -1.0f, 0.0f,
               // VI
               0.0f, 1.0f, 0.0f,
               //
               0.0f, 1.0f, 0.0f,
               //
               0.0f, 1.0f, 0.0f,
               //
               0.0f, 1.0f, 0.0f,
               //
               0.0f, 1.0f, 0.0f,
               //
               0.0f, 1.0f, 0.0f};
    // ATTR_TEXCOORD (VEC2)
    stride += 8;
    textureCoordinates = {// I
                          0.0f, 0.0f,
                          //
                          1.0f, 0.0f,
                          //
                          1.0f, 1.0f,
                          //
                          1.0f, 1.0f,
                          //
                          0.0f, 1.0f,
                          //
                          0.0f, 0.0f,
                          // II
                          0.0f, 0.0f,
                          //
                          1.0f, 0.0f,
                          //
                          1.0f, 1.0f,
                          //
                          1.0f, 1.0f,
                          //
                          0.0f, 1.0f,
                          //
                          0.0f, 0.0f,
                          // III
                          0.0f, 0.0f,
                          //
                          1.0f, 0.0f,
                          //
                          1.0f, 1.0f,
                          //
                          1.0f, 1.0f,
                          //
                          0.0f, 1.0f,
                          //
                          0.0f, 0.0f,
                          // IV
                          0.0f, 0.0f,
                          //
                          1.0f, 0.0f,
                          //
                          1.0f, 1.0f,
                          //
                          1.0f, 1.0f,
                          //
                          0.0f, 1.0f,
                          //
                          0.0f, 0.0f,
                          // V
                          0.0f, 0.0f,
                          //
                          1.0f, 0.0f,
                          //
                          1.0f, 1.0f,
                          //
                          1.0f, 1.0f,
                          //
                          0.0f, 1.0f,
                          //
                          0.0f, 0.0f,
                          // VI
                          0.0f, 0.0f,
                          //
                          1.0f, 0.0f,
                          //
                          1.0f, 1.0f,
                          //
                          1.0f, 1.0f,
                          //
                          0.0f, 1.0f,
                          //
                          0.0f, 0.0f};
    // Make interleaved vertices
    for (size_t i = 0; i < vertices.size() / 3; i++)
    {
        // Vertex positions
        interleavedVertices.push_back(vertices[i * 3 + 0]);
        interleavedVertices.push_back(vertices[i * 3 + 1]);
        interleavedVertices.push_back(vertices[i * 3 + 2]);

        // Normal
        interleavedVertices.push_back(normals[i * 3 + 0]);
        interleavedVertices.push_back(normals[i * 3 + 1]);
        interleavedVertices.push_back(normals[i * 3 + 2]);

        // Texture Coordinates
        interleavedVertices.push_back(textureCoordinates[i * 2 + 0]);
        interleavedVertices.push_back(textureCoordinates[i * 2 + 1]);
    }

    // Drawing indices
    indices = {// Front face
               0, 1, 2, 3, 4, 5,
               // Back face
               6, 7, 8, 9, 10, 11,
               // Left face
               12, 13, 14, 15, 16, 17,
               // Right face
               18, 19, 20, 21, 22, 23,
               // Top face
               24, 25, 26, 27, 28, 29,
               // Bottom face
               30, 31, 32, 33, 34, 35};
}
}
}