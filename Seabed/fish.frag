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


void main()
{

	float disortionx = sin(time * 2) * 0.005;
	float disortiony = cos(time * 2) * 0.005;

	vec2 disortion = vec2(disortionx, disortiony);

	vec2 causticCoord = vec2( (crntPos.x + 15) / 30, (crntPos.z + 15) / 30);

	vec4 color = texture(diffuse0, texCoord + disortion) + vec4(fishColor/2, 0.0);

	float light = texture(caustics, mod(causticCoord + time/16, 1)).r * 0.15 + 0.4;

	FragColor = color * light;

	FragColor.r = pow(FragColor.r, 2) + 0.05;
    FragColor.g = pow(FragColor.g, 2) + 0.15;
    FragColor.b = pow(FragColor.b, 2) + 0.35;
    FragColor.a = 1.0;
}