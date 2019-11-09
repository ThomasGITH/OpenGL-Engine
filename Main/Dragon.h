#pragma once
#include "GameObject.h"
#include "Material.h"
#include <iostream>

class Dragon : public GameObject , Material
{
public:
	Dragon(){}
	Dragon(glm::vec3 position);

	void Update(const bool* keys, const GLfloat& deltaTime) override;

	~Dragon();
private:

};

