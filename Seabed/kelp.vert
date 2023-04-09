#version 430 core

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
float cycle;

mat4 rotx(float ang){
	return mat4(
		1,	0,			 0,		   0,
		0,	cos(ang),	-sin(ang), 0,
		0,	sin(ang),	 cos(ang), 0,
		0,	0,			 0,		   1
	);
}

mat4 roty(float ang){
	return mat4(
		 cos(ang),	0,	sin(ang),	0,
		 0,			1,	0,			0,
		-sin(ang),	0,	cos(ang),	0,
		 0,			0,	0,			1
	);
}

mat4 rotz(float ang){
	return mat4(
		cos(ang),	-sin(ang),	0, 0,
		sin(ang),	 cos(ang),	0, 0,
		0,			 0,			1, 0,
		0,			 0,			0, 1
	);
}


mat4 traslate(vec3 pos){
    return mat4(
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(pos, 1.0));
}

mat4 my_matrix = mat4 (
	1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);


void main()
{

	//vec3 currentDir = vec3(1.0, 0.0, 1.0); 
	// calculates current position
	vec3 scaledPos = aPos * size;
	scaledPos.y = scaledPos.y * lenght;

	//mat4 rotZ = rot_z * aPos.x * aPos.y;
	//mat4 rotX = rot_x * aPos.z * aPos.y;
	//mat4 rotY = rot_y * aPos.y * aPos.x;

	mat4 rot_X = rotx(sin(radians(cycle * 8)) / 8);
	mat4 rot_Y = roty(cos(radians(cycle * 4)) / 4);
	mat4 rot_Z = rotz(cos(radians(cycle * 8)) / 8);

	mat4 rotX = rot_X * aPos.x * aPos.y;
	mat4 rotY = rot_Y * aPos.z * aPos.y;
	mat4 rotZ = rot_Z * aPos.y * aPos.x;

	//mat4 rotZ = aPos.x * aPos.y * rotx();
	//mat4 rotX = rot_x * aPos.z * aPos.y;
	//mat4 rotY = rot_y * aPos.y * aPos.x;

	mat4 current = currentRot * aPos.y * aPos.y * aPos.y;

	
	
	rotX[0][0] = 1;
	rotX[1][1] = 1;
	rotX[2][2] = 1;
	rotX[3][3] = 1;

	rotY[0][0] = 1;
	rotY[1][1] = 1;
	rotY[2][2] = 1;
	rotY[3][3] = 1;

	rotZ[0][0] = 1;
	rotZ[1][1] = 1;
	rotZ[2][2] = 1;
	rotZ[3][3] = 1;

	crntPos = vec3( trans * currentRot * rotX * rotY * rotZ * baseRot * vec4(scaledPos, 1.0f));
	
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}