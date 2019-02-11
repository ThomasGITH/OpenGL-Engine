#pragma once
#include "GameObject.h"
#include "Light.h"

class FlashLight : public GameObject, Light
{
public:
	FlashLight() {}
	FlashLight(glm::vec3 position, glm::vec3 color, GLfloat constant, GLfloat linear, GLfloat quadratic);

	void Update(const bool* keys, const GLfloat& deltaTime) override;

	~FlashLight();
private:

};

