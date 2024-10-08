#version 440 core

struct VertexStruct
{
	vec3 Position;
	vec3 Normal;
	vec3 Tangent;
	vec4 Color;
	vec2 TexCoord;
};
in VertexStruct Vertex;

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0);
}