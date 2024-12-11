#version 330

in vec3 vertexPosition;

out vec4 vPosition;

uniform mat4 mvp;

void main()
{
    vPosition = mvp * vec4(vertexPosition, 1.0);
    gl_Position = vPosition;
}
