#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>
#include "stb_image.h"

class GameObject
{
public:
	GameObject();

	virtual glm::mat4 Update(glm::mat4 model, bool* keys, GLfloat deltaTime);
	glm::mat4 getViewMatrix();
	void calculateCameraView();
	void calculateMouseMovement(GLfloat xChange, GLfloat yChange);

	void createModel(GLfloat *vertices, char* textureLocation, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderModel();
	void clearModel();

	glm::mat4 Transform(glm::mat4 model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float angle);
	glm::vec3 position, scale, rotation, front, up, right, worldUp;
	GLfloat yaw, pitch, moveSpeed, turnSpeed;

	float rotationAngle;
	bool enableCameraCalculations, invertMouse;

	~GameObject();
private:
	GLuint VAO, VBO, IBO, textureID;
	GLsizei indexCount;
	const float toRadians = 3.14159265f / 180.0f;
	char* textureLocation;

	int textureWidth, textureHeight, textureBitDepth;
};

