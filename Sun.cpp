#include "Sun.h"

Sun::Sun(glm::vec3 ambientColour, GLfloat ambientIntensity, glm::vec3 direction, GLfloat diffuseIntensity)
{
	this->colour = ambientColour;
	this->ambientIntensity = ambientIntensity;

	this->direction = direction;
	this->diffuseIntensity = diffuseIntensity;

	setLightType(DIRECTIONAL);
}

glm::mat4 Sun::Update(glm::mat4 model, bool * keys, GLfloat deltaTime)
{
	useLight(getUniformLocation(AMBIENT_COLOUR), getUniformLocation(AMBIENT_INTENSITY), getUniformLocation(DIRECTION), getUniformLocation(DIFFUSE_INTENSITY));
	return Transform(model, position, scale, rotation, rotationAngle);
}


Sun::~Sun()
{
}
