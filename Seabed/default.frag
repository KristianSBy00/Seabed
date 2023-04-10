#version 330 core

out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D normals0;
uniform sampler2D dissortion0;
uniform sampler2D caustics;

uniform vec3 camPos;
uniform float time;
uniform int texRep;

uniform vec3 fish[300];

float disortionx = sin(time * 2) * 0.005;
float disortionz = cos(time * 2) * 0.005;

vec2 disortionCoord = vec2(disortionx, disortionz) + texCoord * texRep;

vec4 direcLight()
{
	// ambient lighting
	float ambient = 0.6f;

	// diffuse lighting
	vec3 normal = texture(normals0, disortionCoord).xyz;

	normal = normalize(normal);

	vec3 lightDirection = normalize(vec3(0.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.9;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, disortionCoord) * (diffuse + ambient) + texture(specular0, disortionCoord).r * specular);
}

float modifier = 1;

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

	for(int i = 0; i < 300; i++){
		vec3 fishPos = fish[i];

		if (fishPos.y <= crntPos.y) continue;

		float fishDist = distance(fishPos.xz, crntPos.xz + vec2(disortionx, disortionz) * 15);

		if ( fishDist < 0.5f ) modifier = modifier * (fishDist/2 + 0.75);
	}

	vec2 causticCoord = vec2( (crntPos.x + 15) / 30, (crntPos.z + 15) / 30);

	vec4 direc_light = direcLight() * (texture(caustics, mod(causticCoord + time/16, 1)).r * 0.5 + 0.5) * modifier;

	FragColor = vec4(direc_light.x, direc_light.y, direc_light.z, 1.0);// + vec4(0.07f, 0.13f, 0.37f, 0.0f);

	FragColor.r = pow(FragColor.r, 2) + 0.05;
    FragColor.g = pow(FragColor.g, 2) + 0.15;
    FragColor.b = pow(FragColor.b, 2) + 0.35;

	if (inCave){
		FragColor = texture(diffuse0, disortionCoord) * 0.5;
		FragColor.a = 1.0;

		FragColor.r = pow(FragColor.r, 2) + 0.05;
		FragColor.g = pow(FragColor.g, 2) + 0.15;
		FragColor.b = pow(FragColor.b, 2) + 0.35;

	}
}