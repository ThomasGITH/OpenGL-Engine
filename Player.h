
#pragma once

#include "GameObject.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Player : public GameObject
{
public:
	Player(glm::vec3 position, float startAngle);

	void Update(const bool* keys, const GLfloat& deltaTime) override;

	~Player();
private:

};

