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

	scale *= 10;

	setMaterialType(DULL);
	createMeshFromScratch(vertices, "Textures/dirt.png", indices, 32, 6, true, false);
}

void Platform::Update(const bool * keys, const GLfloat& deltaTime)
{
	useMaterial(getUniformLocation(SPECULAR_INTENSITY), getUniformLocation(SPECULAR_SHINYNESS));
}

Platform::~Platform()
{
}
