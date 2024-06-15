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

uniform sampler2D Albedo;
uniform sampler2D Normal;
uniform sampler2D Roughness;
uniform sampler2D Metal;

out vec4 FragColor;

void main()
{
	FragColor = texture(Normal, Vertex.TexCoord);
}