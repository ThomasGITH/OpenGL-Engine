#include "Sun.h"

Sun::Sun(glm::vec3 colour, GLfloat ambientIntensity, glm::vec3 direction, GLfloat diffuseIntensity)
{
	this->colour = colour;
	this->ambientIntensity = ambientIntensity;

	this->direction = direction;
	this->diffuseIntensity = diffuseIntensity;

	setLightType(DIRECTIONAL);
}

void Sun::Update(const bool * keys, const GLfloat& deltaTime)
{
	useLight(getUniformLocation(DL_COLOUR), getUniformLocation(DL_AMBIENT_INTENSITY), getUniformLocation(DL_DIRECTION), getUniformLocation(DL_DIFFUSE_INTENSITY), NULL, NULL, NULL, NULL, NULL);
}

Sun::~Sun()
{
}
