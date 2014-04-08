#version 150

in vec2 position;
in vec3 color;
in vec2 texcoord;

out vec3 fragmentColor;
out vec2 uvs;

void main()
{
	uvs = texcoord;
	fragmentColor = color;
    gl_Position = vec4(position, 0.0, 1.0);
}