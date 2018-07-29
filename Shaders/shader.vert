#version 330

layout (location = 0) in vec3 pos;

out vec4 vCol;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * model * vec4(pos, 1.0);
	vCol = vec4(clamp(pos, 1.0f, 0.2f), 1.0f);
}