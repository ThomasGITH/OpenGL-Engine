#include "Lantern.h"

Lantern::Lantern(glm::vec3 position, glm::vec3 color, GLfloat constant, GLfloat linear, GLfloat quadratic)
{
	this->position = position;
	LightPosition = this->position;
	this->colour = color;

	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;

	isPointLight = true;

	setLightType(POINT);
}

glm::mat4 Lantern::Update(glm::mat4 model, bool * keys, GLfloat deltaTime)
{	

	if (keys[GLFW_KEY_U])
	{
		colour = glm::vec3(1.0f, 0.0f, 0.0f);
	}
	if (keys[GLFW_KEY_I])
	{
		colour = glm::vec3(0.0f, 0.0f, 1.0f);
	}

	LightPosition = position;
	useLight(getUniformLocation(POINT_COLOUR), getUniformLocation(POINT_AMBIENT_INTENSITY), NULL, getUniformLocation(POINT_DIFFUSE_INTENSITY),
		getUniformLocation(POINT_POSITION), getUniformLocation(POINT_CONSTANT), getUniformLocation(POINT_LINEAR), getUniformLocation(POINT_QUADRATIC), NULL);
	return Transform(model, position, scale, rotation);
}

Lantern::~Lantern()
{
}
