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

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out VertexStruct Vertex;
out vec3 ViewPosition;

void main()
{
	Vertex = inVertex;
	Vertex.Position = vec3(Model * vec4(inVertex.Position, 1.0));
	Vertex.Normal = mat3(transpose(inverse(Model))) * inVertex.Normal;

	ViewPosition = vec3(View[0][3], View[1][3], View[2][3]);

	gl_Position = Projection * View * Model * vec4(inVertex.Position, 1.0);
}