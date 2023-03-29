#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 crntPos;
//in vec3 Normal;

uniform vec3 camPos;
void main()
{
	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}