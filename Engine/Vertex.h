#pragma once
#include "Typedefs.h"
#include "VertexAttribute.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec4 Color;
	glm::vec2 TexCoord;

	static std::vector<VertexAttribute> GetVertexAttributes()
	{
		std::vector<VertexAttribute> attributes;

		// Position Attribute
		attributes.push_back({
			0,
			3,
			AttributeType::Float,
			false,
			sizeof(Vertex),
			offsetof(Vertex, Position) });

		// Normal Attribute
		attributes.push_back({
			1,
			3,
			AttributeType::Float,
			false,
			sizeof(Vertex),
			offsetof(Vertex, Normal) });

		// Tangent Attribute
		attributes.push_back({
			2,
			3,
			AttributeType::Float,
			false,
			sizeof(Vertex),
			offsetof(Vertex, Tangent) });

		// Color Attribute
		attributes.push_back({
			3,
			4,
			AttributeType::Float,
			false,
			sizeof(Vertex),
			offsetof(Vertex, Color) });

		// TexCoord Attribute
		attributes.push_back({
			4,
			2,
			AttributeType::Float,
			false,
			sizeof(Vertex),
			offsetof(Vertex, TexCoord) });

		return attributes;
	}
};