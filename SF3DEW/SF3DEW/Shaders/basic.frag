#version 150

in vec3 fragmentColor;
in vec2 uvs;

out vec4 outColor;

uniform float brightnessRatio;
uniform vec3 triangleColor;
uniform sampler2D mainTexture;

void main()
{
	vec3 finCol = brightnessRatio * triangleColor;
    outColor = texture(mainTexture, uvs) * vec4(finCol * fragmentColor, 1.0);
}