#version 150

in vec3 fragmentColor;

out vec4 outColor;

uniform float brightnessRatio;
uniform vec3 triangleColor;

void main()
{
	vec3 finCol = brightnessRatio * triangleColor;
    outColor = vec4(finCol * fragmentColor, 1.0);
}