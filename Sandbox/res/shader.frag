#version 410 core

layout (location = 0) out vec4 oColor;

uniform float t;

void main()
{
	float a = cos(t) * 0.5 + 0.5;
	oColor = vec4(a, 0.8 - (a * 0.5), 0.5, 1.0);
}