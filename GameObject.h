#pragma once

#include "Player.h"
#include <glm\glm.hpp>
#include <GL\glew.h>

class GameObject
{
public:
	GameObject();

	virtual glm::mat4 Update(glm::mat4 model);
	void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderMesh();
	void clearMesh();

	float x, y, z, scaleX, scaleY, scaleZ;

	~GameObject();
private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

