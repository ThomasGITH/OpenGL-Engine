#pragma once

#include "GameObject.h"
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Test : public GameObject
{
public:
	Test();

	virtual glm::mat4 Update(glm::mat4 model) override;

	~Test();
private:

};

