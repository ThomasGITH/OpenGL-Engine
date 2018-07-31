#pragma once

#include "GameObject.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class TestObject : public GameObject
{
public:
	TestObject();

	virtual glm::mat4 Update(glm::mat4 model) override;

	~TestObject();
private:
};

class TestObject
{
public:
	TestObject();
	~TestObject();
};

