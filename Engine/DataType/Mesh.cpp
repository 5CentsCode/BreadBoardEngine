#include "Mesh.h"
#include <glad/glad.h>

void UploadMesh(Mesh& mesh, bool dynamic)
{
    mesh.VboIds = { 0, 0, 0, 0, 0, 0 };

    glGenVertexArrays(1, &mesh.VaoId);
    glBindVertexArray(mesh.VaoId);

    uint32 drawType = dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;

    // Position
    int index = 0;
    glGenBuffers(1, &mesh.VboIds[index]);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VboIds[index]);
    glBufferData(GL_ARRAY_BUFFER, mesh.Vertices.size() * sizeof(glm::vec3), mesh.Vertices.data(), drawType);
    glVertexAttribPointer(index, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(index);

    // TexCoords
    index++;
    glGenBuffers(1, &mesh.VboIds[index]);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VboIds[index]);
    glBufferData(GL_ARRAY_BUFFER, mesh.TexCoords.size() * sizeof(glm::vec2), mesh.TexCoords.data(), drawType);
    glVertexAttribPointer(index, 2, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(index);

    // Normals
    index++;
    glGenBuffers(1, &mesh.VboIds[index]);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VboIds[index]);
    glBufferData(GL_ARRAY_BUFFER, mesh.Normals.size() * sizeof(glm::vec3), mesh.Normals.data(), drawType);
    glVertexAttribPointer(index, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(index);

    // Tangents
    index++;
    glGenBuffers(1, &mesh.VboIds[index]);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VboIds[index]);
    glBufferData(GL_ARRAY_BUFFER, mesh.Normals.size() * sizeof(glm::vec3), mesh.Normals.data(), drawType);
    glVertexAttribPointer(index, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(index);

    // Colors
    index++;
    glGenBuffers(1, &mesh.VboIds[index]);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VboIds[index]);
    glBufferData(GL_ARRAY_BUFFER, mesh.Colors.size() * sizeof(Color), mesh.Colors.data(), drawType);
    glVertexAttribPointer(index, 4, GL_UNSIGNED_BYTE, 0, 0, 0);
    glEnableVertexAttribArray(index);

    // Indices
    index++;
    glGenBuffers(1, &mesh.VboIds[index]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.VboIds[index]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.Indices.size() * sizeof(uint16), mesh.Indices.data(), drawType);

    glBindVertexArray(0);
}