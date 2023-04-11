#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 crntPos;
in vec3 frag_normals;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D normal0;
uniform sampler2D dissortion0;
uniform sampler2D caustics;
uniform vec3 camPos;
uniform vec3 fishColor;
uniform float time;
uniform vec3 fish[301];
uniform int fishId;
uniform int big;

float bigShadowDist = -1;
float modifier = 1;

float disortionx = sin(time * 2) * 0.005;
float disortionz = cos(time * 2) * 0.005;

float maxX = 6.271074;
float minX = -4.528926 ;

float maxY = 9.608419;
float minY = -0.391581;

float maxZ = 8.481811;
float minZ = -5.518189;



void main()
{
	bool inCave = true;

	if ( crntPos.x > maxX) inCave = false;
	if ( crntPos.x < minX) inCave = false;

	if ( crntPos.y > maxY) inCave = false;
	if ( crntPos.y < minY) inCave = false;

	if ( crntPos.z > maxZ) inCave = false;
	if ( crntPos.z < minZ) inCave = false;

	for(int i = 0; i < 301; i++){
		
		if(i == fishId){
			continue;
		}

		vec3 fishPos = fish[i];

		float factor = 0.25;

		if (big == 1) factor = 1; 

		if (fishPos.y <= crntPos.y + factor){
			continue;
		}

		float fishDist = distance(fishPos.xz, crntPos.xz + vec2(disortionx, disortionz) * 15);

		if ( fishDist < 0.5f ){
			modifier = modifier * (fishDist + 0.5);
		}
	}

	vec2 disortion = vec2(disortionx, disortionz);

	vec2 causticCoord = vec2( (crntPos.x + 15) / 30, (crntPos.z + 15) / 30);

	vec4 color = texture(diffuse0, texCoord + disortion) + vec4(fishColor/2, 0.0);

	float light = texture(caustics, mod(causticCoord + time/16, 1)).r * 0.5 + 0.5;

	FragColor = color * light * modifier;

	if (inCave){
		FragColor = texture(diffuse0, texCoord + disortion) * 0.5;
		FragColor.a = 1.0;
	}

	FragColor.r = pow(FragColor.r, 2) + 0.05;
    FragColor.g = pow(FragColor.g, 2) + 0.15;
    FragColor.b = pow(FragColor.b, 2) + 0.35;
    FragColor.a = 1.0;
}