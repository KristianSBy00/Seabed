#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTex;

out vec3 frag_normals;
out vec3 crntPos;
out vec2 texCoord;

uniform mat4 camMatrix;
uniform mat4 model;


void main()
{
	texCoord = aTex;
	vec3 guy = aPos * 0.25;

	crntPos = vec3(camMatrix * vec4(guy, 1.0f));

	gl_Position = camMatrix * model * vec4(guy, 1.0f);

	frag_normals = normalize(mat3(model) * aNormal);
	//frag_normals = aNormal;
}