#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

uniform vec3 fishColor;


void main()
{
	// outputs final color
	FragColor = vec4(fishColor, 1.0);
}