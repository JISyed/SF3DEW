#version 150

in vec3 position;
in vec3 color;
in vec2 texcoord;

out vec3 fragmentColor;
out vec2 uvs;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	uvs = texcoord;
	fragmentColor = color;
	mat4 finalMat = projection * view * model;
    gl_Position = finalMat * vec4(position, 1.0);
}