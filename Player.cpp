#include "Player.h"
#include "GameObject.h"
#include <iostream>
#include <glm\glm.hpp>


Player::Player(float x, float y, float z, float startAngle)
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

	this->x = x;
	this->y = y;
	this->z = z;

	rotationAngle = startAngle;
	rotY = 1.0f;
}

bool tri = false;

glm::mat4 Player::Update(glm::mat4 model)
{

	if (abs(x) > 2.5f)
	{
		tri = !tri;
	}

	if (tri) { x += 0.001f; y += 0.001f; }else{ x -= 0.001f; y -= 0.001f;}


	return Transform(model, x, y, z, scaleX, scaleY, scaleZ, rotX, rotY, rotZ, rotationAngle);
}


Player::~Player()
{
}
