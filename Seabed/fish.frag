#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 crntPos;
in vec3 frag_normals;
in vec2 texCoord;

uniform sampler2D tex0;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec3 fishColor;


vec4 pointLight()
{	
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = lightPos - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 0.000001;
	float b = 0.00001;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.30f;

	// diffuse lighting
	vec3 normal = normalize(frag_normals);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return texture(tex0, texCoord) * (diffuse + ambient + specular) * vec4(fishColor, 1.0);
}

void main()
{
	// outputs final color
	//FragColor = pointLight();
	//vec3 lightDirection = normalize(vec3(0.8, -0.5, 0.6));

	//float scalar = max(0, dot(frag_normals, -lightDirection));

	//vec3 lit_cols = fishColor * scalar;

	//FragColor = vec4(lit_cols, 1.0);

	FragColor = pointLight();
}