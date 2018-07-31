
#include "GameObject.h"
#include <iostream>
#include <glm\glm.hpp>

GameObject::GameObject()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;

	scaleX = 0.4f;
	scaleY = 0.4f;
	scaleZ = 1.0f;

	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;

}

void GameObject::createMesh(GLfloat * vertices, unsigned int * indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	//position vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 3, 0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void GameObject::renderMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


glm::mat4 GameObject::Update(glm::mat4 model)
{
	std::cout << "updating from base class (this isn't supposed to happen)" << std::endl;
	return model;
}

glm::mat4 GameObject::Transform(glm::mat4 model, float x, float y, float z, float scaleX, float scaleY, float scaleZ, float rotX, float rotY, float rotZ, float angle)
{
	model = glm::translate(model, glm::vec3(x, y, z));
	if (angle > 360.0f) { angle -= 360.0f; }else if (angle < 0.0f) { angle += 360.0f; }
	model = glm::rotate(model, angle * toRadians, glm::vec3(rotX, rotY, rotZ));
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
	return model;
}

void GameObject::clearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}

GameObject::~GameObject()
{
	clearMesh();
}
