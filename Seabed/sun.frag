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
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform float time;

void main() {
    vec2 center = vec2(0.0, 0.0);
    vec3 lightVec = lightPos - crntPos;

    vec3 baseColor = vec3(1.0, 1.0, 0.5);

    vec4 sunColor = vec4(1.0, 1.0, 0.0, 1.0);

    float dist = distance(center, crntPos.xz);

    vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

    float dist2 = length(dot(crntPos - vec3(0.0, 100.0, 0.0), normalize(lightVec)));

    vec3 color = (baseColor / (dist * dist)) * 10 * ( abs(sin(time/2))/4 + 0.9 );

    vec3 sky = vec3(1.f, 1.0f, 1.0f);

    if (color.r < sky.r) color.r = sky.r;
    if (color.g < sky.g) color.g = sky.g;
    if (color.b < sky.b) color.b = sky.b;

}