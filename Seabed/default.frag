#version 430 core

#define MAX_FISH 500

struct Fish {
    float size;
    vec3 position;
};

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

uniform int numFish;
uniform Fish fish[MAX_FISH];

const float disortionx = sin(time * 2) * 0.005;
const float disortionz = cos(time * 2) * 0.005;

const vec2 disortionCoord = vec2(disortionx, disortionz) + texCoord * texRep;

//cave Shadow;
const float maxX = 6.271074;
const float minX = -4.528926 ;

const float maxY = 9.608419;
const float minY = -0.391581;

const float maxZ = 8.481811;
const float minZ = -5.518189;

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

float fishShadow(){
	float shadowModifier = 1;

	for(int i = 0; i < numFish; i++){
		vec3 fishPos = fish[i].position;

		if (fishPos.y <= crntPos.y) continue;

		float fishDist = distance(fishPos.xz, crntPos.xz + vec2(disortionx, disortionz) * 15);

		if ( fishDist < fish[i].size/2 ) shadowModifier = shadowModifier * fishDist/fish[i].size * 2;
	}

	if (shadowModifier < 0.5) shadowModifier = 0.5;

	return shadowModifier;
}

int caveShadow(){
	if ( crntPos.x > maxX) return 1;
	if ( crntPos.x < minX) return 1;

	if ( crntPos.y > maxY) return 1;
	if ( crntPos.y < minY) return 1;

	if ( crntPos.z > maxZ) return 1;
	if ( crntPos.z < minZ) return 1;
}

vec4 underWaterColor(vec4 basColor){
	return vec4(
		pow(basColor.r, 2) + 0.05,  
		pow(basColor.g, 2) + 0.15, 
		pow(basColor.b, 2) + 0.35,
		1.0
	);
}

float causticLight(){
	vec2 causticCoord = vec2( (crntPos.x + 15) / 30, (crntPos.z + 15) / 30);
	return texture(caustics, mod(causticCoord + time/16, 1)).r * 0.5 + 0.5;
}


void main()
{
	vec4 color = direcLight() * caveShadow() * causticLight() * fishShadow();
	FragColor = underWaterColor(color);
}