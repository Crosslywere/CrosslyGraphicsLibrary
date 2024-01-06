#version 410 core

layout (location = 0) out vec4 oColor;

uniform float t;
uniform vec3 color1;
uniform vec3 color2;

void main()
{
	float a = cos(t) * 0.5 + 0.5;
	vec3 color = mix(color1, color2, a);
	oColor = vec4(color, 1.0);
}