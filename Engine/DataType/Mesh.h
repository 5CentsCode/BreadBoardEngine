#pragma once
#include "Typedefs.h"
#include "Material.h"

struct Mesh
{
    std::vector<glm::vec3> Vertices;
    std::vector<glm::vec2> TexCoords;
    std::vector<glm::vec3> Normals;
    std::vector<glm::vec3> Tangents;
    std::vector<Color> Colors;
    std::vector<uint16> Indices;

    uint32 VaoId;
    std::vector<uint32> VboIds;
};

void UploadMesh(Mesh& mesh, bool dynamic);