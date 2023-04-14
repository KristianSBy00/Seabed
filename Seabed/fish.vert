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
uniform float swimCycle;
uniform int big;
uniform float size;

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


void main()
{
	texCoord = aTex;

	vec3 scaledPos = aPos * 0.25 * size;
	scaledPos.z = scaledPos.z * 0.65;

	vec3 stupid = aPos * 0.25;

	mat4 swRotZ = roty(  stupid.z *			cos(radians(swimCycle * 64	+ stupid.z * 180  )	) / 6);
	mat4 swRotX = rotx( (stupid.z/16 + 2) *	cos(radians(swimCycle * 32)							) / 32);
	mat4 swRotY = rotz( (stupid.y*3 - 0.5)  *	cos(radians(swimCycle * 64	+ (stupid.y * 3 - 0.5) * 180))/2);
	mat4 swTran = traslate(vec3( sin(radians(swimCycle*16)) / 16 , cos(radians(swimCycle*16 + 180)) / 16, sin(radians(swimCycle*16 + 180) / 64)));

	crntPos = vec3(model * swTran * swRotX * swRotY * swRotZ * vec4(scaledPos, 1.0f));


	gl_Position = camMatrix * vec4(crntPos, 1.0f);
}