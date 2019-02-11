#include "Player.h"
#include "GameObject.h"
#include <iostream>
#include <glm\glm.hpp>
#include "Locator.h"

Player::Player(glm::vec3 position, float startAngle)
{
	this->position = position;
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	rotation.y = -30.0f; //pitch
	rotation.x = 0.0f; //yaw

	moveSpeed = 3.0f;
	turnSpeed = 0.1f;
	
	enableMouseCameraCalculations = true;

	tag = "player";
}

void Player::Update(const bool * keys, const GLfloat& deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;
	
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
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

	if (keys[GLFW_KEY_O])
	{
		rotation.x += 5.0f;
	}

	if (keys[GLFW_KEY_5])
	{
		GameObject& flash = Locator::FindObjectByTag("flashlight");
		std::cout << flash.moveSpeed << std::endl;
		Locator::RemoveGameObject("flashlight");
	}
}

Player::~Player()
{
}
