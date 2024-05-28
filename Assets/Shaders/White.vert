#version 440 core

struct Vertex_s
{
	vec3 Position;
};

layout (location = 0) in Vertex_s Vertex;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = vec4(Vertex.Position, 1.0);
}