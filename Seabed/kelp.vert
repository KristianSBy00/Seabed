#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 crntPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;

uniform sampler2D dissortion0;

uniform mat4 camMatrix;

uniform float size;
uniform float lenght;

uniform mat4 rot_x;
uniform mat4 rot_y;
uniform mat4 rot_z;
uniform mat4 currentRot;

uniform mat4 trans;
uniform mat4 baseRot;
uniform mat4 model;

float time;

void main()
{

	vec3 currentDir = vec3(1.0, 0.0, 1.0); 

	// calculates current position
	vec3 scaledPos = aPos * size;
	scaledPos.y = scaledPos.y * lenght;

	mat4 rotZ = rot_z * aPos.x * aPos.y;
	mat4 rotX = rot_x * aPos.z * aPos.y;
	mat4 rotY = rot_y * aPos.y * aPos.x;

	mat4 current = currentRot * aPos.y * aPos.y * aPos.y;

	rotZ[0][0] = 1;
	rotZ[1][1] = 1;
	rotZ[2][2] = 1;
	rotZ[3][3] = 1;

	rotX[0][0] = 1;
	rotX[1][1] = 1;
	rotX[2][2] = 1;
	rotX[3][3] = 1;

	rotY[0][0] = 1;
	rotY[1][1] = 1;
	rotY[2][2] = 1;
	rotY[3][3] = 1;

	mat4 newModel = trans * currentRot * rotY * rotX * rotZ * baseRot;

	crntPos = vec3(newModel * vec4(scaledPos, 1.0f));

	mat4 glslNormMatrix = transpose(inverse(newModel));

	vec4 tmpNorm = vec4(aNormal, 1.0);

	tmpNorm = glslNormMatrix * tmpNorm;
	Normal = normalize(vec3(tmpNorm.x, tmpNorm.y, tmpNorm.z));

	color = aColor;
	texCoord = aTex;
	
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}