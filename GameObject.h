
#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <glm\gtc\matrix_transform.hpp>


class GameObject
{
public:
	GameObject();

	virtual glm::mat4 Update(glm::mat4 model);

	void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderMesh();
	void clearMesh();

	glm::mat4 Transform(glm::mat4 model, float x, float y, float z, float scaleX, float scaleY, float scaleZ, float rotX, float rotY, float rotZ, float angle);

	float x, y, z, scaleX, scaleY, scaleZ, rotX, rotY, rotZ;
	float rotationAngle;
	const float toRadians = 3.14159265f / 180.0f;

	~GameObject();
private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

