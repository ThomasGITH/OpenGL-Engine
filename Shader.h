#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

class Shader
{
public:
	Shader();

	void createFromFile(const char* vertexLocation, const char* fragmentLocation);
	std::string readFile(const char* fileLocation);
	void processShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void useShader();
	void clearShader();
	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();

	~Shader();
private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;
};

