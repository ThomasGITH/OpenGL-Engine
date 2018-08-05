#include "Player.h"
#include "GameObject.h"
#include <iostream>
#include <glm\glm.hpp>


Player::Player(glm::vec3 position, float startAngle)
{

	this->position = position;
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -60.0f;
	pitch = 0.0f;

	moveSpeed = 5.0f;
	turnSpeed = 0.1f;

	enableCameraCalculations = true;
	invertMouse = false;
	calculateCameraView();
}


glm::mat4 Player::Update(glm::mat4 model, bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}

	if (keys[GLFW_KEY_E])
	{
		position += up * velocity;
	}
	if (keys[GLFW_KEY_Q])
	{
		position -= up * velocity;
	}

	return Transform(model, position, scale, rotation, rotationAngle);
}


Player::~Player()
{
}
