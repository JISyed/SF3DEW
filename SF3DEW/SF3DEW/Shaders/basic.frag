#version 150

out vec4 outColor;

uniform float brightnessRatio;

void main()
{
	float bri = brightnessRatio;
    outColor = vec4(bri, bri, bri, 1.0);
}