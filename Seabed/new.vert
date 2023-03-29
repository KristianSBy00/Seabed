#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aNormal;


out vec3 Normal;
out vec3 crntPos;

uniform mat4 camMatrix;
uniform mat4 model;


void main()
{
	//Normal = aNormal;

	vec3 guy = aPos * 2;

	crntPos = vec3(camMatrix * vec4(guy, 1.0f));

	gl_Position = camMatrix * model * vec4(guy, 1.0f);

	//gl_Position = camMatrix * model * vec4(guy, 1.0);
}