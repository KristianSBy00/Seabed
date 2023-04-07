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
uniform mat4 trans;
uniform float swimCycle;
uniform mat4 rot_x;
uniform mat4 rot_y;
uniform mat4 rot_z;


mat4 BuildTranslation(vec3 delta)
{
    mat4 m;
    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[3] = vec4(delta, 1.0);
    return m;
}


void main()
{
	texCoord = aTex;
	vec3 scaledPos = aPos * 0.25;

	mat4 rotY = rot_y * (scaledPos.z * scaledPos.z * 1);

	rotY[0][0] = 1;
	rotY[1][1] = 1;
	rotY[2][2] = 1;
	rotY[3][3] = 1;

	mat4 rotZ = rot_z * (scaledPos.y - 0.25) * 4;

	rotZ[0][0] = 1;
	rotZ[1][1] = 1;
	rotZ[2][2] = 1;
	rotZ[3][3] = 1;

	crntPos = vec3(model * trans * rotY * rot_x * rotZ * vec4(scaledPos, 1.0f));


	gl_Position = camMatrix * vec4(crntPos, 1.0f);

	frag_normals = normalize(mat3(model * trans * rotY * rot_x * rotZ) * aNormal);
}