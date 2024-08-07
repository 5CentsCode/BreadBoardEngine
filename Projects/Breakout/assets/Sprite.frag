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

uniform sampler2D Sprite;
uniform vec3 ColorTint;

out vec4 FragColor;

void main()
{
	FragColor = texture(Sprite, Vertex.TexCoord) * vec4(ColorTint, 1.0);
}