
#include "GameObject.h"
#include <iostream>
#include <glm\glm.hpp>

GameObject::GameObject()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;

	scale.x = 0.4f;
	scale.y = 0.4f;
	scale.z = 1.0f;

	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;

	enableCameraCalculations = false;
	invertMouse = false;

	textureID = 0;
	textureWidth = 0;
	textureHeight = 0;
	textureBitDepth = 0;
	textureLocation = 0;
}

void GameObject::createModel(GLfloat * vertices, char* textureLocation, unsigned int * indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
	this->textureLocation = textureLocation;

	unsigned char *textureData = stbi_load(this->textureLocation, &textureWidth, &textureHeight, &textureBitDepth, 0);
	if (!textureData)
	{
		printf("Failed to find %s\n", this->textureLocation);
		return;
	}

	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	//position vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
	glEnableVertexAttribArray(0);

	//texture vertices
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

}

void GameObject::renderModel()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


glm::mat4 GameObject::Update(glm::mat4 model, bool* keys, GLfloat deltaTime)
{
	std::cout << "updating from base class (this isn't supposed to happen)" << std::endl;
	return model;
}

glm::mat4 GameObject::Transform(glm::mat4 model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float angle)
{
	model = glm::translate(model, position);
	if (angle > 360.0f) { angle -= 360.0f; }else if (angle < 0.0f) { angle += 360.0f; }
	model = glm::rotate(model, angle * toRadians, rotation);
	model = glm::scale(model, scale);
	return model;
}

void GameObject::calculateCameraView()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

	front.y = invertMouse ? front.y * -1 : front.y;
}

void GameObject::calculateMouseMovement(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	pitch = glm::clamp(pitch, -89.0f, 89.0f);

	if (enableCameraCalculations)
	{
		calculateCameraView();
	}
}

glm::mat4 GameObject::getViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void GameObject::clearModel()
{
	std::cout << "removing mesh" << std::endl;
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

	if (textureID != 0)
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}

	textureWidth = 0;
	textureHeight = 0;
	textureBitDepth = 0;
	textureLocation = 0;

	indexCount = 0;
}

GameObject::~GameObject()
{
	clearModel();
}
