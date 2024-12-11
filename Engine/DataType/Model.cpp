#include "Model.h"
#include <glad/glad.h>
#include <tiny_obj_loader.h>
#include "Components/Transform.h" // TEMP
#include "Components/Camera.h" // TEMP

Model LoadModel(const char* fileName)
{
    Model model;

    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(fileName, reader_config))
    {
        if (!reader.Error().empty())
        {
            // std::cerr << "TinyObjReader: " << reader.Error();
        }
        return model;
    }

    if (!reader.Warning().empty())
    {
        // std::cout << "TinyObjReader: " << reader.Warning();
        return model;
    }

    const tinyobj::attrib_t& attrib = reader.GetAttrib();
    const std::vector<tinyobj::shape_t>& shapes = reader.GetShapes();
    // const std::vector<tinyobj::material_t>& materials = reader.GetMaterials();

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++)
    {
        Mesh mesh;
        mesh.VaoId = 0;

        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++)
            {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                glm::vec3 vertex
                {
                    attrib.vertices[3 * size_t(idx.vertex_index) + 0],
                    attrib.vertices[3 * size_t(idx.vertex_index) + 1],
                    attrib.vertices[3 * size_t(idx.vertex_index) + 2]
                };
                mesh.Vertices.push_back(vertex);

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    glm::vec3 normal
                    {
                        attrib.normals[3 * size_t(idx.normal_index) + 0],
                        attrib.normals[3 * size_t(idx.normal_index) + 1],
                        attrib.normals[3 * size_t(idx.normal_index) + 2]
                    };
                    mesh.Normals.push_back(normal);
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                    glm::vec2 texCoord
                    {
                        attrib.texcoords[2 * size_t(idx.texcoord_index) + 0],
                        attrib.texcoords[2 * size_t(idx.texcoord_index) + 1]
                    };
                    mesh.TexCoords.push_back(texCoord);
                }

                // Optional: vertex colors
                Color color
                {
                    attrib.colors[3 * size_t(idx.vertex_index) + 0],
                    attrib.colors[3 * size_t(idx.vertex_index) + 1],
                    attrib.colors[3 * size_t(idx.vertex_index) + 2],
                    1.0f
                };
                mesh.Colors.push_back(color);

                mesh.Indices.push_back((uint16)mesh.Indices.size());
            }

            index_offset += fv;

            // per-face material
            // shapes[s].mesh.material_ids[f];
        }

        UploadMesh(mesh, false);
        model.Meshes.push_back(mesh);
    }

    return model;
}