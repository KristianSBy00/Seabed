#version 330 core

out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D normal0;
uniform sampler2D dissortion0;
uniform sampler2D caustics;

uniform vec3 camPos;
uniform float time;
uniform float texRep;

void main()
{
	vec2 causticCoord = vec2( (crntPos.x + 15) / 30, (crntPos.z + 15) / 30);

	//vec3 normal = texture(diffuse0, causticCoord * texRep).xyz;
	//vec4 direc_light = direcLight();

	float disortionx = sin(time * 2) * 0.005;
	float disortiony = cos(time * 2) * 0.005;

	vec2 disortion = vec2(disortionx, disortiony);

	vec3 direc_light = texture(diffuse0, texCoord * texRep + disortion).xyz;

	direc_light = direc_light * (texture(caustics, mod(causticCoord + time/16, 1)).r * 0.15 + 0.4);

	FragColor = vec4(direc_light.x, direc_light.y, direc_light.z, 1.0);// + vec4(0.07f, 0.13f, 0.37f, 0.0f);

	FragColor.r = pow(FragColor.r, 2) + 0.05;
    FragColor.g = pow(FragColor.g, 2) + 0.15;
    FragColor.b = pow(FragColor.b, 2) + 0.35;
    FragColor.a = 1.0;
}