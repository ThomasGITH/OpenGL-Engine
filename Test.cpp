#include "Test.h"

Test::Test()
{

	//schrijf hier de vertex-arrays
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z	
		-1.0f, -1.0f, -0.6f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -0.6f,
		0.0f, 1.0f, 0.0f
	};

	createMesh(vertices, indices, 12, 12);

}

float angle;

glm::mat4 Test::Update(glm::mat4 model)
{

	angle += 0.1f;
	if (angle > 360)
	{
		angle -= 360;
	}

	std::cout << "test" << std::endl;

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -2.5f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
	model = glm::rotate(model, angle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	return model;
}


Test::~Test()
{
}
