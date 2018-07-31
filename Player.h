
#pragma once

#include "GameObject.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Player : public GameObject
{
public:
	Player(float x, float y, float z, float startAngle);

	virtual glm::mat4 Update(glm::mat4 model) override;

	~Player();
private:

};

