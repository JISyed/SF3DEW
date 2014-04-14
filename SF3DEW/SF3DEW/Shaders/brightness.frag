#version 150

uniform vec4 meshColor;
uniform sampler2D mainTexture;
uniform float brightnessRatio;

in vec4 vertexColor;
in vec2 vertexUVs;

out vec4 outColor;

void main()
{
	vec4 brightnessAdjustedColor = brightnessRatio * meshColor;
	vec4 texel = texture(mainTexture, vertexUVs);
    outColor = texel * brightnessAdjustedColor * vertexColor;
}