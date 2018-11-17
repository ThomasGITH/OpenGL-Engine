#pragma once
#include "GameObject.h"
#include "Material.h"
#include <iostream>

class Platform : public GameObject, Material
{
public:
	Platform(){}
	Platform(glm::vec3 position);

	glm::mat4 Update(glm::mat4 model, bool* keys, GLfloat deltaTime) override;

	~Platform();
};

