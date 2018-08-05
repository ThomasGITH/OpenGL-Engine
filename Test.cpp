#include "Test.h"
#include "GameObject.h"
#include <iostream>
#include <glm\glm.hpp>


Test::Test(glm::vec3 position, float startAngle)
{

	//schrijf hier de vertex-arrays
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z		  u    v	
		-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,
		1.0f, -1.0f, -0.6f,		1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f
	};

	createModel(vertices, "Textures/dirt.png", indices, 12, 12);

	this->position = position;

	rotationAngle = startAngle;
	rotation.y = 1.0f;
}

glm::mat4 Test::Update(glm::mat4 model, bool* keys, GLfloat deltaTime)
{

	return Transform(model, position, scale, rotation, rotationAngle);
}


Test::~Test()
{
}
