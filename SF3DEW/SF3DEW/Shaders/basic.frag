#version 150

uniform vec4 meshColor;
uniform sampler2D mainTexture;

in vec4 vertexColor;
in vec2 vertexUVs;

out vec4 outColor;

void main()
{
	vec4 texel = texture(mainTexture, vertexUVs);
    outColor = texel * meshColor * vertexColor;
}