#version 440 core

struct VertexStruct
{
	vec3 Position;
	vec3 Normal;
	vec3 Tangent;
	vec4 Color;
	vec2 TexCoord;
};
layout (location = 0) in VertexStruct inVertex;

uniform mat4 View;
uniform mat4 Projection;

out VertexStruct Vertex;

void main()
{
	Vertex = inVertex;

	gl_Position = Projection * View * vec4(Vertex.Position, 1.0);
}