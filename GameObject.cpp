
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

	enableMouseCameraCalculations = false;
	invertMouse = false;
	disableCameraClamp = false;
	isPointLight = false;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	textureID = 0;
	textureWidth = 0;
	textureHeight = 0;
	textureBitDepth = 0;
	textureLocation = 0;

	moveSpeed = 2.5f;
}

void GameObject::createModel(GLfloat * vertices, char* textureLocation, unsigned int * indices, unsigned int numOfVertices, unsigned int numOfIndices, bool calculateNormals)
{
	this->textureLocation = textureLocation;
	
	unsigned char *textureData = stbi_load(this->textureLocation, &textureWidth, &textureHeight, &textureBitDepth, 0);
	if (!textureData)
	{
		printf("Failed to find %s\n", this->textureLocation);
		return;
	}

	if(calculateNormals)
	{
		vertices = calcAverageNormals(indices, numOfIndices, vertices, numOfVertices, 8, 5);
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

glm::mat4 GameObject::Transform(glm::mat4 model, glm::vec3 position, glm::vec3 scale, glm::vec3 eulerAngle)
{
	model = glm::translate(model, position);

	if (!enableMouseCameraCalculations) {
		if (rotation.y < 0) { rotation.y += 360; } else if (rotation.y > 360) { rotation.y -= 360; }
		if (rotation.x < 0) { rotation.x += 360; } else if (rotation.x > 360) { rotation.x -= 360; }
		if (rotation.z < 0) { rotation.z += 360; } else if (rotation.z > 360) { rotation.z -= 360; }
	}
	
	glm::mat4 rotationMatrix = glm::toMat4(glm::quat(glm::radians(eulerAngle)));

	model *= rotationMatrix;
	model = glm::scale(model, scale);

	return model;
}

void GameObject::calculateMouseMovement(GLfloat mouseXChange, GLfloat mouseYChange)
{
	if (enableMouseCameraCalculations)
	{
		mouseXChange *= turnSpeed;
		mouseYChange *= turnSpeed;
		
		rotation.x += mouseXChange;
		rotation.y += mouseYChange;

		rotation.y = disableCameraClamp ? rotation.y : glm::clamp(rotation.y, -89.0f, 89.0f);
	}

	//Calculate the front, right and up vectors (very important)
	front.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	front.y = sin(glm::radians(rotation.y));
	front.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

	front.y = invertMouse ? front.y * -1 : front.y;
}

glm::mat4 GameObject::getViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void GameObject::setUniformLocations(GLuint uniformAmbientColour, GLuint uniformAmbientIntensity, GLuint uniformDirection, GLuint uniformDiffuseIntensity, GLuint uniformSpecularIntensity, GLuint uniformShinyness)
{
	this->uniformColour = uniformAmbientColour;
	this->uniformAmbientIntensity = uniformAmbientIntensity;
	this->uniformDirection = uniformDirection;
	this->uniformDiffuseIntensity = uniformDiffuseIntensity;
	this->uniformSpecularIntensity = uniformSpecularIntensity;
	this->uniformShinyness = uniformShinyness;
}

void GameObject::setPointLightUniforms(GLuint uniformColour, GLuint uniformAmbientIntensity, GLuint uniformDiffuseIntensity, GLuint uniformPosition, GLuint uniformConstant, GLuint uniformLinear, GLuint uniformQuadrant)
{
	pointLight.uniformColour = uniformColour;
	pointLight.uniformAmbientIntensity = uniformAmbientIntensity;
	pointLight.uniformDiffuseIntensity = uniformDiffuseIntensity;
	pointLight.uniformPosition = uniformPosition;
	pointLight.uniformConstant = uniformConstant;
	pointLight.uniformLinear = uniformLinear;
	pointLight.uniformQuadrant = uniformQuadrant;
}

void GameObject::setSpotLightUniforms(GLuint uniformColour, GLuint uniformAmbientIntensity, GLuint uniformDiffuseIntensity, GLuint uniformPosition, GLuint uniformConstant, GLuint uniformLinear, GLuint uniformQuadrant, GLuint uniformEdge, GLuint uniformDirection)
{
	spotLight.uniformColour = uniformColour;
	spotLight.uniformAmbientIntensity = uniformAmbientIntensity;
	spotLight.uniformDiffuseIntensity = uniformDiffuseIntensity;
	spotLight.uniformPosition = uniformPosition;
	spotLight.uniformConstant = uniformConstant;
	spotLight.uniformLinear = uniformLinear;
	spotLight.uniformQuadrant = uniformQuadrant;
	spotLight.uniformEdge = uniformEdge;
	spotLight.uniformDirection = uniformDirection;
}

GLuint GameObject::getUniformLocation(uniform location)
{
	switch (location)
	{
	case DL_COLOUR: return uniformColour; break;
	case DL_AMBIENT_INTENSITY: return uniformAmbientIntensity; break;
	case DL_DIRECTION: return uniformDirection; break;
	case DL_DIFFUSE_INTENSITY: return uniformDiffuseIntensity; break;

	case SPECULAR_INTENSITY: return uniformSpecularIntensity; break;
	case SPECULAR_SHINYNESS: return uniformShinyness; break;

	case POINT_COLOUR: return pointLight.uniformColour; break;
	case POINT_AMBIENT_INTENSITY: return pointLight.uniformAmbientIntensity; break;
	case POINT_DIFFUSE_INTENSITY: return pointLight.uniformDiffuseIntensity; break;
	case POINT_POSITION: return pointLight.uniformPosition; break;
	case POINT_CONSTANT: return pointLight.uniformConstant; break;
	case POINT_LINEAR: return pointLight.uniformLinear; break;
	case POINT_QUADRATIC: return pointLight.uniformQuadrant; break;

	case SPOT_COLOUR: return spotLight.uniformColour; break;
	case SPOT_AMBIENT_INTENSITY: return spotLight.uniformAmbientIntensity; break;
	case SPOT_DIFFUSE_INTENSITY: return spotLight.uniformDiffuseIntensity; break;
	case SPOT_POSITION: return spotLight.uniformPosition; break;
	case SPOT_CONSTANT: return spotLight.uniformConstant; break;
	case SPOT_LINEAR: return spotLight.uniformLinear; break;
	case SPOT_QUADRATIC: return spotLight.uniformQuadrant; break;
	case SPOT_EDGE: return spotLight.uniformEdge; break;
	case SPOT_DIRECTION: return spotLight.uniformDirection; break;
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
