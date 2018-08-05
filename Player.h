
#pragma once

#include "GameObject.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Player : public GameObject
{
public:
	Player(glm::vec3 position, float startAngle);

	virtual glm::mat4 Update(glm::mat4 model, bool* keys, GLfloat deltaTime) override;

	~Player();
private:

};

