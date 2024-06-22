#version 440 core

struct LightStruct
{
    int Type;

	vec3 Position;
	vec3 Direction;
	vec3 Color;

	float Range;
	float Angle;
	float Intensity;
	float Attenuation;
};

struct MaterialStruct
{
	sampler2D Albedo;
	sampler2D Normal;
	sampler2D Roughness;
	sampler2D Metal;
};

struct VertexStruct
{
	vec3 Position;
	vec3 Normal;
	vec3 Tangent;
	vec4 Color;
	vec2 TexCoord;
};

in VertexStruct Vertex;
in vec3 ViewPosition;

uniform MaterialStruct Material;
uniform LightStruct Light;


out vec4 FragColor;

void main()
{
	FragColor = vec4(Light.Color.rgb * texture(Material.Albedo, Vertex.TexCoord).rgb, 1.0);
}