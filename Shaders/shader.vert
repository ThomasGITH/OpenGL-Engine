#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 vCol;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
	
	TexCoord = tex;

	//Multiplies "norm" with "model" for positional data/converting to world-coordinates (norm is only the direction)
	//Inverses & transposes for non-uniform scaling
	Normal = mat3(transpose(inverse(model))) * norm;
	
	//For specular lighting
	//Get the world position
	//Not actually the fragment-position yet
	//.xyz to convert to a Vec3
	FragPos = (model * vec4(pos, 1.0)).xyz; 
}
