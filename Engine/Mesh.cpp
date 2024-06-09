#include "Mesh.h"
#include "Mesh.h"
#include "Mesh.h"
#include "Mesh.h"
#include <glad/glad.h>
#include "Vertex.h"

Mesh::Mesh(Guid& guid, std::string& name, std::vector<Vertex>& vertices, std::vector<uint32>& indices)
	: Resource(guid, name)
{
	m_vertices = vertices;
	m_indices = indices;

	m_vao = 0;
	m_vbo = 0;
	m_vao = 0;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);

	m_vertices.clear();
	m_indices.clear();
}

void Mesh::Upload(bool dynamic)
{
	// TODO: check dirty state of mesh, and see if the mesh should be reuploaded
	if (m_vao > 0)
	{
		return;
	}

	uint32 drawType = dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), drawType);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * m_indices.size(), m_indices.data(), drawType);

	for (const VertexAttribute& attribute : Vertex::GetVertexAttributes())
	{
		glEnableVertexAttribArray(attribute.LayoutLocation);
		glVertexAttribPointer(attribute.LayoutLocation,
			attribute.Count,
			attribute.Type,
			attribute.Normalize,
			attribute.Stride,
			(const void*)attribute.Offset);
	}
}

void Mesh::Bind()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}

uint32 Mesh::GetIndexCount() const
{
	return uint32(m_indices.size());
}
