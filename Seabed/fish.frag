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
uniform vec3 fish[300];
uniform int fishId;

float bigShadowDist = -1;
float modifier = 1;

float disortionx = sin(time * 2) * 0.005;
float disortionz = cos(time * 2) * 0.005;

void main()
{
	for(int i = 0; i < 300; i++){
		
		if(i == fishId){
			continue;
		}

		vec3 fishPos = fish[i];

		if (fishPos.y <= crntPos.y + 0.25){
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

	FragColor.r = pow(FragColor.r, 2) + 0.05;
    FragColor.g = pow(FragColor.g, 2) + 0.15;
    FragColor.b = pow(FragColor.b, 2) + 0.35;
    FragColor.a = 1.0;
}