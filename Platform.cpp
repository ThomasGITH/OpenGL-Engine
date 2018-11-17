#include "Platform.h"

Platform::Platform(glm::vec3 position)
{
	this->position = position;

	unsigned int indices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat vertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	setMaterialType(SHINY);
	createModel(vertices, "Textures/dirt.png", indices, 32, 6, false);
}

glm::mat4 Platform::Update(glm::mat4 model, bool * keys, GLfloat deltaTime)
{
	useMaterial(getUniformLocation(SPECULAR_INTENSITY), getUniformLocation(SPECULAR_SHINYNESS));
	return Transform(model, position, scale, rotation);
}

Platform::~Platform()
{
}
