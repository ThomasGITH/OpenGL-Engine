#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Texture
{
public:
	Texture(){}
	Texture(const char* fileLoc);
	
	bool LoadTexture();
	bool LoadTextureA();

	void RenderTexture();
	void ClearTexture();

	~Texture();
private:

	GLuint textureID;
	int width, height, bitDepth;

	const char* fileLocation;
};

