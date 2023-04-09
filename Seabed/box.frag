#version 330 core

out vec4 FragColor;

in vec3 crntPos;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D normals0;
uniform sampler2D dissortion0;
uniform sampler2D caustics;
uniform float time;

void main()
{
	vec2 causticCoord = vec2( (crntPos.x + 15) / 30, (crntPos.z + 15) / 30);

	FragColor = vec4(0.17f, 0.33f, 0.57f, 0.95f) * (texture(caustics, mod(causticCoord + time/16, 1)).r * 0.5 + 0.5);// + vec4(0.07f, 0.13f, 0.37f, 0.0f);
}