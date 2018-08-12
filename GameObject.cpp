
#include "GameObject.h"
#include <iostream>
#include <glm\glm.hpp>
#include "Locator.h"

GameObject::GameObject()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;

	scale.x = 0.4f;
	scale.y = 0.4f;
	scale.z = 0.4f;

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

	vertices = calcAverageNormals(indices, numOfIndices, vertices, numOfVertices, 8, 5);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);

	//texture vertices
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	//normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);
	
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

GLfloat* GameObject::calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}

	return vertices;
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

void GameObject::setUniformLocations(GLuint uniformAmbientColour, GLuint uniformAmbientIntensity, GLuint uniformDirection, GLuint uniformDiffuseIntensity)
{
	this->uniformAmbientColour = uniformAmbientColour;
	this->uniformAmbientIntensity = uniformAmbientIntensity;
	this->uniformDirection = uniformDirection;
	this->uniformDiffuseIntensity = uniformDiffuseIntensity;
}

GLuint GameObject::getUniformLocation(uniform location)
{
	switch (location)
	{
	case AMBIENT_COLOUR: return uniformAmbientColour; break;
	case AMBIENT_INTENSITY: return uniformAmbientIntensity; break;
	case DIRECTION: return uniformDirection; break;
	case DIFFUSE_INTENSITY: return uniformDiffuseIntensity; break;
	default: break;
	}
}

void GameObject::clearModel()
{
	std::cout << "clearing OGL Objects" << std::endl;
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
