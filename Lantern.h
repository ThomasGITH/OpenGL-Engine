#pragma once
#include "GameObject.h"
#include "Light.h"

class Lantern : public GameObject, Light
{
public:
	Lantern(){}
	Lantern(glm::vec3 position, glm::vec3 color, GLfloat constant, GLfloat linear, GLfloat quadratic);

	virtual glm::mat4 Update(glm::mat4 model, bool* keys, GLfloat deltaTime) override;

	~Lantern();
private:

};

