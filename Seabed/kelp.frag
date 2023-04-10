#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 crntPos;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D normal0;
uniform sampler2D caustics;

uniform vec3 camPos;

uniform float time;
uniform vec3 fish[300];

float modifier = 1;

void main()
{


	bool shadow = false;

	for(int i = 0; i < 300; i++){
		vec3 fishPos = fish[i];

		if (fishPos.y <= crntPos.y){
			continue;
		};

		float fishDist = distance(fishPos.xz, crntPos.xz);

		if ( fishDist < 0.5f ){
			modifier = modifier * (fishDist + 0.5);

			shadow = true;
		}
	}

	vec4 direc_light = vec4(0.2, 0.7, 0.2, 0.0);

	vec2 causticCoord = vec2( (crntPos.x + 15) / 30, (crntPos.z + 15) / 30);

	direc_light = direc_light * (texture(caustics, mod(causticCoord + time/16, 1)).r * 0.5 + 0.5);

	FragColor = vec4(direc_light.x, direc_light.y, direc_light.z, 1.0);

	if(shadow){
		FragColor = direc_light * modifier;
		FragColor.a = 1.f;
	}

	FragColor.r = pow(FragColor.r, 2) + 0.05;
    FragColor.g = pow(FragColor.g, 2) + 0.15;
    FragColor.b = pow(FragColor.b, 2) + 0.35;
    FragColor.a = 1.0;
}