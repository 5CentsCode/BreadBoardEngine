#pragma once
#include "Resource.h"
#include "Vertex.h"

class Mesh : public Resource
{
public:

	Mesh(Guid& guid, std::string& name, std::vector<Vertex>& vertices, std::vector<uint32>& indices);
	~Mesh();

public:

	void Upload(bool dynamic);
	void Bind();

	int32 GetIndexCount() const; // TEMP

private:
	std::vector<Vertex> m_vertices;
	std::vector<uint32> m_indices;

	uint32 m_vao;
	uint32 m_vbo;
	uint32 m_ebo;
};
