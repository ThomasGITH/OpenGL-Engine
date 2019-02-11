#pragma once
#include "GameObject.h"
#include "Light.h"
#include <glm\glm.hpp>

class Sun : public GameObject, Light
{
public:
	Sun(){}
	Sun(glm::vec3 colour, GLfloat ambientIntensity, glm::vec3 direction, GLfloat diffuseIntensity);
	
	void Update(const bool* keys, const GLfloat& deltaTime) override;

	~Sun();
private:

};

