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
uniform mat4 Projection;

out VertexStruct Vertex;

void main()
{
	mat3 inverseModel = mat3(transpose(inverse(Model)));

	Vertex = inVertex;
	Vertex.Position = vec3(Model * vec4(inVertex.Position, 1.0));
	Vertex.Normal = inverseModel * inVertex.Tangent;
	Vertex.Normal = inverseModel * inVertex.Normal;

	gl_Position = Projection * Model * vec4(inVertex.Position, 1.0);
}