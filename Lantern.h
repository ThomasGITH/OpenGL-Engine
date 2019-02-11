#pragma once
#include "GameObject.h"
#include "Light.h"

class Lantern : public GameObject, Light
{
public:
	Lantern(){}
	Lantern(glm::vec3 position, glm::vec3 color, GLfloat constant, GLfloat linear, GLfloat quadratic);

	void Update(const bool* keys, const GLfloat& deltaTime) override;

	~Lantern();
private:

};

