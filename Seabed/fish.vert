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
uniform mat4 tra;

mat4 BuildTranslation(vec3 delta)
{
    mat4 m;
    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[3] = vec4(delta, 1.0);
    return m;
}

uniform mat4 rot;

void main()
{
	texCoord = aTex;
	vec3 scaledPos = aPos * 0.25;

	mat4 nRot = rot * scaledPos.z;

	nRot[0][0] = 1;
	nRot[1][1] = 1;
	nRot[2][2] = 1;
	nRot[3][3] = 1;

	mat4 even_trans = BuildTranslation(vec3(0, 0, 0.5));

	crntPos = vec3(camMatrix * vec4(scaledPos, 1.0f));

	gl_Position = camMatrix * model * tra * nRot * even_trans * vec4(scaledPos, 1.0f);

	frag_normals = normalize(mat3(model * tra * nRot * even_trans) * aNormal);
}