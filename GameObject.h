#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>
#include "stb_image.h"
#include <vector>

class Locator;

class GameObject
{
public:
	GameObject();
	
	virtual glm::mat4 Update(glm::mat4 model, bool* keys, GLfloat deltaTime) = 0;
	void setUniformLocations(GLuint uniformAmbientColour, GLuint uniformAmbientIntensity, GLuint uniformDirection, GLuint uniformDiffuseLocation);
	glm::mat4 getViewMatrix();
	enum uniform {AMBIENT_COLOUR, AMBIENT_INTENSITY, DIRECTION, DIFFUSE_INTENSITY};
	GLuint getUniformLocation(uniform location);
	void calculateCameraView();
	void calculateMouseMovement(GLfloat xChange, GLfloat yChange);

	void createModel(GLfloat *vertices, char* textureLocation, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderModel();
	GLfloat* calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset);
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
	GLuint uniformAmbientColour, uniformAmbientIntensity, uniformDirection, uniformDiffuseIntensity;
};

