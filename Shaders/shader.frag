#version 330

in vec4 vCol;
in vec2 texCoords;

out vec4 colour;

uniform sampler2D myTexture;

void main()
{
	colour = texture(myTexture, texCoords);
}