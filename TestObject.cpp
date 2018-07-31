#include "TestObject.h"
#include <iostream>
#include <glm\glm.hpp>


TestObject::TestObject()
{

	//schrijf hier de vertex-arrays
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z	
		-1.0f, -1.0f, -0.6f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -0.6f,
		0.0f, 1.0f, 0.0f
	};

	createMesh(vertices, indices, 12, 12);

}

float curangle;

glm::mat4 TestObject::Update(glm::mat4 model)
{
	//std::cout << "UPDATING PLAYER" << std::endl;

	curangle += 0.01f;
	if (curangle > 360)
	{
		curangle -= 360;
	}

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
	model = glm::rotate(model, curangle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	return model;
}


Player::~Player()
{
}
