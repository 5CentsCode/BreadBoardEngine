#include "ResourceManager.h"
#include <filesystem>
#include <fstream>
#include <vector>
#define TINYOBJ_LOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "Mesh.h"
#include "Shader.h"
#include "Vertex.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

std::shared_ptr<Shader> ResourceManager::LoadShader(std::string name, std::string vertex, std::string fragmentFile)
{
	Guid guid = GetGuid(name);
	assert(m_resources.find(guid) == m_resources.end());

	std::vector<char> vertexSource = ReadFile(vertex);
	std::vector<char> fragmentSource = ReadFile(fragmentFile);

	std::shared_ptr<Shader> newShader = std::make_shared<Shader>(guid, name, vertexSource, fragmentSource);
	m_resources.emplace(guid, newShader);

	return newShader;
}

std::shared_ptr<Mesh> ResourceManager::LoadMesh(std::string filepath)
{
	Guid guid = GetGuid(filepath);
	assert(m_resources.find(guid) == m_resources.end());

	tinyobj::ObjReaderConfig reader_config;
	reader_config.mtl_search_path = "./"; // Path to material files

	tinyobj::ObjReader reader;

	if (!reader.ParseFromFile(filepath, reader_config))
	{
		if (!reader.Error().empty())
		{
			printf("%s\n", reader.Error().c_str());
		}
		return nullptr;
	}

	if (!reader.Warning().empty())
	{
		printf("%s\n", reader.Warning().c_str());
		return nullptr;
	}

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	// auto& materials = reader.GetMaterials();

	std::vector<Vertex> vertices;
	std::vector<uint32> indices;

	// Loop over shapes
	for (uint64 s = 0; s < shapes.size(); s++)
	{
		// Loop over faces(polygon)
		uint64 index_offset = 0;
		for (uint64 f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			uint64 fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (uint64 v = 0; v < fv; v++)
			{
				Vertex vertex = {};

				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

				int32 vertexIndex = idx.vertex_index * 3;
				vertex.Position.x = attrib.vertices[vertexIndex + 0];
				vertex.Position.y = attrib.vertices[vertexIndex + 1];
				vertex.Position.z = attrib.vertices[vertexIndex + 2];

				if (idx.normal_index >= 0)
				{
					int32 normalIndex = idx.normal_index * 3;
					vertex.Normal.x = attrib.normals[normalIndex + 0];
					vertex.Normal.y = attrib.normals[normalIndex + 1];
					vertex.Normal.z = attrib.normals[normalIndex + 2];
				}

				if (idx.texcoord_index >= 0)
				{
					int32 texCoordIndex = idx.texcoord_index * 2;
					vertex.TexCoord.x = attrib.texcoords[texCoordIndex + 0];
					vertex.TexCoord.y = attrib.texcoords[texCoordIndex + 1];
				}

				int32 colorIndex = vertexIndex;
				vertex.Color.r = attrib.colors[colorIndex + 0];
				vertex.Color.g = attrib.colors[colorIndex + 1];
				vertex.Color.b = attrib.colors[colorIndex + 2];

				vertices.push_back(vertex);
				indices.push_back(uint32(indices.size()));
			}
			index_offset += fv;

			// per-face material
			// shapes[s].mesh.material_ids[f];
		}
	}

	std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>(guid, filepath, vertices, indices);
	newMesh->Upload(false);
	m_resources.emplace(guid, newMesh);

	return newMesh;
}

void ResourceManager::Clear()
{
	m_resources.clear();
}

std::vector<char> ResourceManager::ReadFile(std::string& filePath)
{
	std::vector<char> buffer;
	bool fileExists = std::filesystem::exists(filePath);
	if (fileExists)
	{
		std::ifstream file(filePath);
		buffer.resize((uint64)std::filesystem::file_size(filePath));
		file.read(buffer.data(), buffer.size());
		file.close();
	}

	return buffer;
}

Guid ResourceManager::GetGuid(std::string name)
{
	std::string lowercaseString = name;
	std::transform(name.begin(), name.end(), lowercaseString.begin(), [](char ch)
	{
		return (char)std::tolower((int32)ch);
	});
	Guid guid = std::hash<std::string>{}(lowercaseString);
	return guid;
}
