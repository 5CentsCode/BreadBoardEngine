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

struct VertexStruct
{
	vec3 Position;
	vec3 Normal;
	vec3 Tangent;
	vec4 Color;
	vec2 TexCoord;
};

in VertexStruct Vertex;
in vec3 FragPos;

uniform sampler2D AlbedoTex;
uniform sampler2D NormalTex;
uniform sampler2D RoughnessTex;
uniform sampler2D MetalTex;
uniform LightStruct Lights;

out vec4 FragColor;

void main()
{
	vec4 ambient = vec4(Lights.Color * Lights.Intensity, 1.0);

	vec3 norm = normalize(Vertex.Normal);
	vec3 lightDir = normalize(Lights.Position - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * vec4(Lights.Color, 1.0);

	FragColor = (ambient + diffuse) * texture(AlbedoTex, Vertex.TexCoord);
}