#version 430 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;


uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D normal0;
uniform sampler2D caustics;
uniform sampler2D normalTex;
uniform vec3 camPos;
uniform float time;

 vec2 causticCoord = vec2( (crntPos.x + 15) / 30, (crntPos.z + 15) / 30);

float direcLight()
{
	// ambient lighting
	float ambient = 0.60f;

	// diffuse lighting
	//vec3 normal = normalize(Normal);
	vec3 normal = normalize(texture(normalTex, causticCoord + time/16).xyz);

	vec3 lightDirection = normalize(vec3(0.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.2f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return diffuse + ambient + (1 - texture(caustics, mod(causticCoord + time/16, 1)).r) * specular;
}

void main() {
    //float light = texture(caustics, mod(causticCoord + time/16, 1)).r * 0.5;
    FragColor = vec4(0.17f, 0.33f, 0.57f, 0.85f) * direcLight();//+ vec4(0.1f, 0.1f, 0.1f, 0.0f)) * light;
}