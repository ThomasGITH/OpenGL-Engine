#include "Test.h"
#include "GameObject.h"
#include <iostream>
#include <glm\glm.hpp>

Test::Test(glm::vec3 position, float startAngle, char* textureLocation)
{

	//schrijf hier de vertex-arrays
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z		  u    v		 nx	   ny	 nz
		-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	createMeshFromScratch(vertices, textureLocation, indices, 32, 12, true, true);

	this->position = position;

	setMaterialType(SHINY);
	scale *= 10;

	moveSpeed = 3.0f;
}

void Test::Update(const bool * keys, const GLfloat& deltaTime)
{
	rotation.y += 0.27f;
	
	float velocity = moveSpeed * deltaTime;

	useMaterial(getUniformLocation(SPECULAR_INTENSITY), getUniformLocation(SPECULAR_SHINYNESS));
}


Test::~Test()
{
}
