#version 330

in vec4 vPosition;

out vec4 finalColor;

void main()
{
    vec3 magenta = vec3(1.0, 0.0f, 0.859);
    int modulus = (int(floor(vPosition.x)) + int(floor(vPosition.y)) + int(floor(vPosition.z))) % 2;
    vec3 modColor = (modulus % 2) * magenta;

    finalColor = vec4(modColor, 1.0);
}