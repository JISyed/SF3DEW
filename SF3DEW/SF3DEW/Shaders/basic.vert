#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 position;
in vec4 color;
in vec2 uvs;

out vec4 vertexColor;
out vec2 vertexUVs;

void main()
{
	// Send attributes down to fragment shader
	vertexUVs = uvs;
	vertexColor = color;

	// Calculate final position on screen
	mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(position, 1.0);
}