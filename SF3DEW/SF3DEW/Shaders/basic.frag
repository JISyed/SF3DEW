#version 150

in vec3 fragmentColor;
in vec2 uvs;

out vec4 outColor;

uniform float brightnessRatio;
uniform vec4 meshColor;
uniform sampler2D mainTexture;

void main()
{
	vec3 finCol = brightnessRatio * meshColor.rgb;
    outColor = texture(mainTexture, uvs) * vec4(finCol * fragmentColor, 1.0);
}