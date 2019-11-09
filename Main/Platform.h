#pragma once
#include "GameObject.h"
#include "Material.h"
#include <iostream>

class Platform : public GameObject, Material
{
public:
	Platform(){}
	Platform(glm::vec3 position);

	void Update(const bool* keys, const GLfloat& deltaTime) override;

	~Platform();
};

