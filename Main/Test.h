#pragma once

#include "GameObject.h"
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Locator.h"
#include "Material.h"

class Test : public GameObject, Material
{
public:
	Test(){}
	Test(glm::vec3 position, float startAngle, char* textureLocation);

	void Update(const bool* keys, const GLfloat& deltaTime) override;

	~Test();
private:

};

