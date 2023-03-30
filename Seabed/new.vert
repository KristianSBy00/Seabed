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
uniform mat4 rot;


float guy_guy = 0;

mat4 BuildTranslation(vec3 delta)
{
    mat4 m;
    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[3] = vec4(delta, 1.0);
    return m;
}

//fish dims
//min	-0,121728	-0,769018	-4,812853
//max	 0,121734	 1,31762	 0,248223

void main()
{
	texCoord = aTex;

	mat4 new_rot = rot * ((aPos.z)/5);

	
	new_rot[0][0] = 1;
	new_rot[1][1] = 1;
	new_rot[2][2] = 1;
	new_rot[3][3] = 1;

	crntPos = vec3(camMatrix * vec4(aPos, 1.0f));

	gl_Position = camMatrix * model * new_rot * vec4(aPos, 1.0f);

	frag_normals = normalize(mat3(model * new_rot) * aNormal);
	//frag_normals = aNormal;
}