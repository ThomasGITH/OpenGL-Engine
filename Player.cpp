#include "Player.h"
#include <iostream>
#include <glm\glm.hpp>

Player::Player()
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

	createMesh(vertices,indices,12,12);

}

glm::mat4 Player::Update(glm::mat4 model)
{
	//std::cout << "UPDATING PLAYER" << std::endl;

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

	return model;
}


Player::~Player()
{
}
